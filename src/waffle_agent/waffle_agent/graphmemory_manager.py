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

from waffle_agent.common_utils import format_pose_msg

class BatchSemanticGraph(Node):
    def __init__(self):
        super().__init__('batch_semantic_graph')

        self.declare_parameter("pose_topic", "/odom")
        self.declare_parameter("label_topic", "/labels")
        self.declare_parameter("top_k_return", 5)  # Objects returned from sevice calls
        
        # Hyperparameters
        self.SPATIAL_THRESH = 2.0  # Meters
        self.ANGLE_THRESH = np.radians(60) # +/- 60 degrees field of view
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

    # CALLBACK TO KEEP ROBOT POSITION UPDATED
    def pose_callback(self, msg: Odometry):
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
                node_yaw = data['pos'][2]
                angle_diff = abs(np.arctan2(np.sin(current_yaw - node_yaw), np.cos(current_yaw - node_yaw)))
                
                if angle_diff < self.ANGLE_THRESH:
                    nearby_nodes.append((node_id, data))

        # GROUP INPUTS BY SEMANTICS
        # Input: ['cup', 'cup', 'cup', 'mouse'] -> {'cup': 3, 'mouse': 1}
        incoming_counts = Counter(labels_in_frame)

        # MATCHING LOGIC
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
                # Case A: We see MORE than we knew. 
                # Action: Update all known ones, create (seen - known) new ones.
                
                # Update existing (Refresh timestamp/position)
                for nid in existing_matches:
                    self.update_node(nid, current_pose)
                
                # Create NEW nodes
                num_to_create = count_seen - count_known
                for _ in range(num_to_create):
                    self.create_node(label, embedding, current_pose)
                    
            else:
                # Case B: We see FEWER or EQUAL to what we knew.
                # Action: Just update the closest 'count_seen' nodes.
                # (We don't delete the extras immediately; maybe they are occluded)
                
                # Sort existing matches by distance to current robot pose to update the most likely ones
                # (Optional refinement)
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

    def update_node(self, node_id, pose):
        # Update logic (e.g., moving average of position, refresh timestamp)
        self.graph.nodes[node_id]['last_seen'] = self.get_clock().now()
        # We generally DON'T update the position heavily here because 
        # 'pose' is where the robot is NOW, not where the object is.
        # But we could pull the node slightly closer to the current robot pose.
        self.get_logger().info(f"Updated {node_id}")

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


def main():
    rclpy.init()
    node = BatchSemanticGraph()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

