from pyexpat import model
import rclpy
from rclpy.node import Node
from tf2_ros import Buffer, TransformListener
import networkx as nx
import numpy as np
from sentence_transformers import SentenceTransformer
from collections import Counter
import json

# Messages
from nav_msgs.msg import Odometry
from std_msgs.msg import String
from visualization_msgs.msg import Marker, MarkerArray

# CUSTOM INTERFACES FOR SERVICES
# Make sure you built the 'waffle_agent_msgs' package
from waffle_agent_msgs.srv import SearchByLabel, SearchByPosition
from waffle_agent_msgs.msg import GraphResult

# Graph nodes visualization
import matplotlib.pyplot as plt

# Utils for Odometry formatting
from waffle_agent.common_utils import format_pose_msg

class BatchSemanticGraph(Node):
    def __init__(self):
        super().__init__('batch_semantic_graph')

        self.declare_parameter("pose_topic", "/odom")
        self.declare_parameter("label_topic", "/labels")
        self.declare_parameter("top_k_return", 10)  # Objects returned from sevice calls
        
        # Hyperparameters
        self.SPATIAL_THRESH = 4.0  # Meters
        self.ANGLE_THRESH = np.radians(359.999) # +/- 60 degrees field of view
        self.SEMANTIC_THRESH = 0.75

        # Embedder & Graph
        self.model = SentenceTransformer('sentence-transformers/all-MiniLM-L6-v2')
        self.graph = nx.Graph()
        self.node_id_counter = 1

        # ROS Setup
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        #self.marker_pub = self.create_publisher(MarkerArray, '/memory_graph_markers', 10)
        
        self.pose_subscriber = self.create_subscription(
            Odometry,
            self.get_parameter("pose_topic").value,
            self.pose_callback,
            10
        )

        # Florence subscriber
        self.caption_subscriber = self.create_subscription(
            String,
            self.get_parameter("label_topic").value,
            self.labels_callback,
            10
        )

        ### Services
        self.srv_search_by_label = self.create_service(
            SearchByLabel, 
            'search_by_label', 
            self.labelsearch_callback
        )

        self.srv_search_by_position = self.create_service(
            SearchByPosition, 
            'search_by_position', 
            self.positionsearch_callback
        )

        # ADDED VISUALIZATION OF NODES: Setup Matplotlib for real-time plotting
        plt.ion()  # Interactive mode on
        self.fig, self.ax = plt.subplots()
        self.ax.set_title("Semantic Graph State")
        self.ax.set_xlabel("X [m]")
        self.ax.set_ylabel("Y [m]")
        self.ax.grid(True)

        # Create a timer to update the plot at 2Hz (every 0.5s)
        # This prevents blocking your main sensor callbacks
        self.viz_timer = self.create_timer(1.0, self.update_plot)

    # CALLBACK TO KEEP ROBOT POSITION UPDATED
    def pose_callback(self, msg: Odometry):
        self.get_logger().info("Received pose...")
        self.pose_msg = msg
        #self.logger.info("Received pose message (MARKPOSE)")

    # CALLBACK TO PROCESS INCOMING LABELS IN A BATCH
    def labels_callback(self, msg):
        try:
            # Decode the JSON string back into a Python list
            # "[\"car\", \"wheel\", \"wheel\"]" -> ['car', 'wheel', 'wheel']
            labels_in_frame = json.loads(msg.data)
            self.get_logger().info("Received labels_in_frame.")
            
        except json.JSONDecodeError:
            self.get_logger().error("Failed to decode incoming labels JSON.")
            return

        if not labels_in_frame:
            self.get_logger().info("No labels in received data pack")
            return

        # 1. Get the current robot pose
        #pose = self.pose_msg
        
        if self.pose_msg:
            # 2. Pass the list directly to the batch processor
            self.process_batch(labels_in_frame)
            
            # 3. Update Rviz
            #self.publish_markers()
        else: self.get_logger().error("No odometry received")

    def process_batch(self, labels_in_frame):
        """
        labels_in_frame: list of strings ['cup', 'cup', 'bottle']
        current_pose: tuple (x, y, yaw)
        """
        
        position, angle, pose_time = format_pose_msg(self.pose_msg)
        current_x = position[0]
        current_y = position[1]
        current_yaw = angle
        current_pose = (current_x, current_y, current_yaw)

        # FIND RELEVANT EXISTING NODES (Spatial & Angular Gating)
        # We only want to match against nodes that are CLOSE and in FRONT of us.
        nearby_nodes = []
        
        for node_id, data in self.graph.nodes(data=True):
            node_x, node_y, _ = data['pos'] # Node stores where robot WAS
            
            # Distance Check
            dist = np.linalg.norm([current_x - node_x, current_y - node_y])
            
            if dist < self.SPATIAL_THRESH:
                # Angle THRESHOLD Check
                node_yaw = data['pos'][2] # Yaw of the robot when node was detected
                angle_diff = abs(np.arctan2(np.sin(current_yaw - node_yaw), np.cos(current_yaw - node_yaw)))
                
                if angle_diff < self.ANGLE_THRESH:
                    nearby_nodes.append((node_id, data)) ## SET OF NODES CONSIDERED "CLOSE" FOR THE CURRENT POS+ORIENTATION

            #else: self.get_logger().info(f"Previous pos: {data['pos']}\nCurrent pos: {current_pose}")

        #### GROUP INPUTS BY SEMANTICS: 
        # process based on the known number of surrounding nodes for the current pos+orientation
        # Input: ['cup', 'cup', 'cup', 'mouse'] -> {'cup': 3, 'mouse': 1}
        incoming_counts = Counter(labels_in_frame)

        # MATCHING LOGIC
        # Handles possibility that current object is being detected with a different label
        # of equivalent semantic meaning w.r.t. a previous detection of the same object
        # (e.g. "Cup" and "Mug" will have very similar 'sim' score, so we avoid having semantic duplicates)
        for label, count_seen in incoming_counts.items():
            embedding = self.model.encode(label)
            
            # Find how many nodes of this type we ALREADY know about in this area
            existing_matches = []
            for nid, data in nearby_nodes:
                # Semantic Similarity Check
                sim = np.dot(embedding, data['embedding']) / (
                    np.linalg.norm(embedding) * np.linalg.norm(data['embedding'])
                )
                if sim > self.SEMANTIC_THRESH:
                    existing_matches.append(nid)
            
            count_known = len(existing_matches)
            
            # RECONCILE
            if count_seen > count_known:
                # CASE A: WE SEE MORE THAN WE KNEW. 
                # Action: Update all known ones, create (seen - known) new ones.
                
                # Update existing (Refresh timestamp/position)
                for nid in existing_matches:
                    self.update_node(nid, current_pose)
                
                # Create NEW nodes
                num_to_create = count_seen - count_known
                for _ in range(num_to_create):
                    self.create_node(label, embedding, current_pose)
                    
            else:
                # CASE B: WE SEE FEWER or EQUAL TO WHAT WE KNEW.
                # Action: Just update the closest 'count_seen' nodes.
                # (We don't delete the extras immediately; maybe they are occluded)
                # TODO: HANDLE OBJECTS NOT BEING SEEN (DELETE NODES)
                for i in range(count_seen):
                    self.update_node(existing_matches[i], current_pose)

    def create_node(self, label, embedding, pose):
        # Jitter so markers don't overlap perfectly in Rviz
        #jx = np.random.uniform(-0.1, 0.1)
        #jy = np.random.uniform(-0.1, 0.1)
        jx = 0
        jy = 0
        display_pose = (pose[0]+jx, pose[1]+jy, pose[2])

        self.graph.add_node(
            self.node_id_counter,
            label=label,
            embedding=embedding,
            pos=display_pose, 
            last_seen=self.get_clock().now()
        )
        self.get_logger().info(f"Created NEW {label} (ID: {self.node_id_counter})")
        self.node_id_counter += 1

    def update_node(self, node_id, current_robot_pose):
        # 1. Get the old position data
        old_x, old_y, _ = self.graph.nodes[node_id]['pos']
        
        # 2. Get the new observation (Current Robot Position)
        new_x, new_y, _ = current_robot_pose

        # 3. Moving Average Logic
        # alpha controls how fast the node moves towards the new position.
        # 0.1 = very stable, 1.0 = jumps instantly to new position.
        alpha = 0.5 

        updated_x = (old_x * (1 - alpha)) + (new_x * alpha)
        updated_y = (old_y * (1 - alpha)) + (new_y * alpha)

        # 4. Save back to Graph
        # We keep the original yaw or update it, usually yaw is less critical for point objects
        self.graph.nodes[node_id]['pos'] = (updated_x, updated_y, current_robot_pose[2])
        self.graph.nodes[node_id]['last_seen'] = self.get_clock().now()
        
        # Log strictly for debugging (optional)
        self.get_logger().info(f"Refined Pos for ID {node_id}: ({updated_x:.2f}, {updated_y:.2f})")

    #def publish_markers(self):
    #    # ADD FOR RVIZ
    #    pass


#    def labelsearch_callback(self, request, response):
#        query_vec = self.model.encode(request.query_text)
#        scores = []
#    
#        for node, data in self.graph.nodes(data=True):
#            # Calculate cosine similarity: (A · B) / (||A|| * ||B||)
#            sim = np.dot(query_vec, data['embedding']) / (np.linalg.norm(query_vec) * np.linalg.norm(data['embedding']))
#            scores.append((node, sim))
        
        # Sort by highest similarity
#        response.top_kresults = sorted(scores, key=lambda x: x[1], reverse=True)[:self.get_parameter("top_k_return").value]

#        return response

    def labelsearch_callback(self, request, response):
        # Request comes in as 'query_text' (string)
        query_vec = self.model.encode(request.query_text)
        candidates = []
    
        # Calculate Scores
        for node_id, data in self.graph.nodes(data=True):
            sim = np.dot(query_vec, data['embedding']) / (np.linalg.norm(query_vec) * np.linalg.norm(data['embedding']))
            candidates.append((node_id, data, sim))

        top_k = sorted(candidates, key=lambda x: x[2], reverse=True)[:self.get_parameter("top_k_return").value]

        # Create GRAPHRESULT custom message
        results_list = []
        for nid, data, score in top_k:
            res = GraphResult()
            res.node_id = int(nid)
            res.label = str(data['label'])
            res.score = float(score)
            res.position = [float(x) for x in data['pos']] # Ensure simple float list
            results_list.append(res)

        # Assign to response
        response.top_k_results = results_list
        return response

#    def positionsearch_callback(self, request, response):
#        scores = []
    
#        for node, data in self.graph.nodes(data=True):
#            node_pos = np.array(data['pos'])
#            dist = np.linalg.norm(np.array(request.query_position) - node_pos)
#            scores.append((node, dist))
        
        # Sort by closest distance
#        response.top_kresults = sorted(scores, key=lambda x: x[1])[:self.get_parameter("top_k_return").value]

#        return response

    def positionsearch_callback(self, request, response):
        candidates = []
        target_pos = np.array(request.query_position)
    
        for node_id, data in self.graph.nodes(data=True):
            node_pos = np.array(data['pos']) # [x, y, theta]
            
            # FIX: Only use X and Y (indices 0 and 1) for distance ---
            # We assume the first 2 elements are always X and Y.
            # We ignore theta (index 2) for the distance score.
            xy_node = node_pos[:2]
            xy_target = target_pos[:2]
            
            dist = np.linalg.norm(xy_target - xy_node)
            # ------------------------------------------------------------
            
            candidates.append((node_id, data, dist))
        
        # Sort by distance
        top_k = sorted(candidates, key=lambda x: x[2])[:self.get_parameter("top_k_return").value]

        results_list = []
        for nid, data, dist in top_k:
            res = GraphResult()
            res.node_id = int(nid)
            res.label = str(data.get('label', 'unknown'))
            res.score = float(dist)
            
            # We still RETURN the full [x, y, theta] so the robot knows orientation
            res.position = [float(x) for x in data['pos']] 
            
            results_list.append(res)

        response.top_k_results = results_list
        return response
    


    def update_plot(self):
        # Skip if no data
        if not hasattr(self, 'pose_msg') or self.pose_msg is None:
            return

        self.ax.clear()
        self.ax.grid(True, linestyle='--', alpha=0.5)
        self.ax.set_title(f"Semantic Graph: {self.graph.number_of_nodes()} Nodes")
        
        # --- SWAPPED AXIS LABELS ---
        self.ax.set_xlabel("Y [m] (Left/Right)")
        self.ax.set_ylabel("X [m] (Forward/Back)")

        # 1. Extract Robot Position
        rx = self.pose_msg.pose.pose.position.x
        ry = self.pose_msg.pose.pose.position.y
        
        # 2. Center View (X is vertical, Y is horizontal)
        self.ax.set_xlim(ry - 5, ry + 5)
        self.ax.set_ylim(rx - 5, rx + 5)
        self.ax.invert_xaxis()  # <--- KEEPS LEFT/RIGHT CORRECT

        # 3. Draw Robot (Red Triangle pointing up)
        # We plot (y, x) because of the swap
        self.ax.plot(ry, rx, marker='^', color='red', markersize=15, label='Robot', zorder=10)

        # 4. Draw Graph Nodes
        if self.graph.number_of_nodes() > 0:
            xs = [] # Vertical pos
            ys = [] # Horizontal pos
            labels = []
            
            # Extract data including ID
            for node_id, data in self.graph.nodes(data=True):
                xs.append(data['pos'][0])
                ys.append(data['pos'][1])
                # Format: "label (id)"
                labels.append(f"{data.get('label', '?')} ({node_id})")
            
            # Plot Nodes (Blue Circles)
            # alpha=0.5 helps see overlapping nodes
            self.ax.scatter(ys, xs, c='blue', s=100, alpha=0.5, edgecolors='k', zorder=5)

            # Annotate with Background Box for Readability
            for i, txt in enumerate(labels):
                self.ax.annotate(
                    txt, 
                    (ys[i], xs[i]), 
                    xytext=(0, 5),                  # Shift text slightly up
                    textcoords='offset points', 
                    ha='center', 
                    fontsize=9, 
                    fontweight='bold',
                    bbox=dict(boxstyle="round,pad=0.2", fc="white", alpha=0.7, ec="none") # White background
                )

        self.ax.legend(loc='upper right')
        plt.draw()
        plt.pause(0.001)


#def main():
#    rclpy.init()
#    node = BatchSemanticGraph()
#    rclpy.spin(node)
#    node.destroy_node()
#    rclpy.shutdown()

def main():
    rclpy.init()
    node = BatchSemanticGraph()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        plt.close('all')  # Close the plot window
        node.destroy_node()
        rclpy.shutdown()
