import time
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import requests

# --- FIXED IMPORT FOR LANGCHAIN 0.3 ---
from langchain_core.tools import tool
# ---------------------------------------
#It was:
#from langchain.agents import tool, Tool

# GRAPH-SEARCH NECESSARY
import json
import ast
# Import the services so we can create the clients
from waffle_agent_msgs.srv import SearchByLabel, SearchByPosition

# Global references to be set by the main agent
NODE: Node = None
CMD_VEL_PUB = None
LATEST_ODOM = None

def init_waffle_tools(node: Node):
    """Initialize the global node and publishers for the tools."""
    global NODE, CMD_VEL_PUB
    NODE = node
    CMD_VEL_PUB = NODE.create_publisher(Twist, "/cmd_vel", 10)
    NODE.create_subscription(Odometry, "/odom", _odom_callback, 10)
    NODE.get_logger().info("Waffle Tools initialized.")

def _odom_callback(msg):
    global LATEST_ODOM
    LATEST_ODOM = msg

@tool
def move_waffle(linear: float = 0.2, angular: float = 0.0, duration: float = 2.0):
    """Move the TurtleBot3 Waffle with given linear and angular velocities."""
    if NODE is None:
        return "Error: ROS Node not initialized in tools."

    vel = Twist()
    vel.linear.x = float(linear)
    vel.angular.z = float(angular)
    
    rate_hz = 10
    start_time = NODE.get_clock().now().nanoseconds
    duration_ns = duration * 1e9
    
    NODE.get_logger().info(f"Moving: lin={linear}, ang={angular}, dur={duration}")

    while (NODE.get_clock().now().nanoseconds - start_time) < duration_ns:
        CMD_VEL_PUB.publish(vel)
        time.sleep(1.0 / rate_hz) 
    
    CMD_VEL_PUB.publish(Twist())  # stop
    return f"Moved with linear={linear}, angular={angular} for {duration} sec."

@tool
def get_waffle_pose():
    """Get the robot's current position from /odom."""
    global LATEST_ODOM
    attempts = 0
    while LATEST_ODOM is None and attempts < 10:
        time.sleep(0.5)
        attempts += 1

    if LATEST_ODOM:
        pos = LATEST_ODOM.pose.pose.position
        return f"Robot is at x={pos.x:.2f}, y={pos.y:.2f}."
    else:
        return "Odometry data not available yet."

@tool
def query_long_term_memory(query: str):
    """
    Queries the robot's long-term memory (Vector DB).
    """
    if NODE:
        NODE.get_logger().info(f"Querying LTM with: '{query}'")

    try:
        resp = requests.post("http://localhost:8000/query", json={"query": query}, timeout=100)
        if resp.status_code != 200:
            return f"Error from Remembr server: {resp.text}"
        data = resp.json()
        pos = data.get("position")
        if pos:
            if NODE: NODE.get_logger().info(f"The Retrieved position was: '{pos}'")
            return f"Memory query successful. Location: {data['text']}. Position: [x={pos[0]:.2f}, y={pos[1]:.2f}, z={pos[2]:.2f}]."
        else:
            if NODE: NODE.get_logger().info(f"No position found. Details: '{data['text']}'")
            return f"Memory query successful, but no position found. Details: {data['text']}"
    except Exception as e:
        if NODE: NODE.get_logger().error(f"Failed to query Remembr server: {e}")
        return f"Error querying Remembr server: {e}"

@tool
def query_graph_memory_semantical(query: str):
    """
    Queries the robot's graph memory for semantically similar entries.
    Input: A description of what to find (e.g. "kitchen objects", "danger").
    """
    global NODE
    if NODE is None:
        return "Error: ROS Node not initialized."

    # Create Client
    client = NODE.create_client(SearchByLabel, 'search_by_label')
    if not client.wait_for_service(timeout_sec=1.0):
        return "Error: Semantic Graph Service is offline."

    # Build Request
    req = SearchByLabel.Request()
    req.query_text = query

    # Call Service
    future = client.call_async(req)
    
    # Wait for result (Using the global NODE to spin)
    rclpy.spin_until_future_complete(NODE, future)
    
    # Parse Result
    if future.result() is not None:
        response = future.result()
        
        output = []
        for item in response.top_k_results:
            output.append({
                "id": item.node_id,
                "label": item.label,
                "similarity": round(item.score, 2),
                "pos": [round(p, 3) for p in item.position]
            })
        return json.dumps(output)
    else:
        return f"Error: {future.exception()}"


@tool
def query_graph_memory_positional(query: str):
    """
    Queries the robot's graph memory for positionally close nodes.
    Input: A string list of coordinates [x, y, radians] (e.g. "[1.0, 2.0, 1.7]").
    """
    global NODE
    if NODE is None:
        return "Error: ROS Node not initialized."

    # Parse Input String -> Float List
    try:
        # Tries JSON "[1, 2]" first, falls back to Python literal
        try:
            coords = json.loads(query)
        except:
            coords = ast.literal_eval(query)
        query_pos = [float(x) for x in coords]
    except:
        return "Error: Input must be a coordinate list like '[x, y, theta]'."

    # Create Client
    client = NODE.create_client(SearchByPosition, 'search_by_position')
    if not client.wait_for_service(timeout_sec=1.0):
        return "Error: Positional Graph Service is offline."

    # Build Request + Call service
    req = SearchByPosition.Request()
    req.query_position = query_pos
    future = client.call_async(req)
    
    # Wait for result
    rclpy.spin_until_future_complete(NODE, future)
    
    # Parse Result
    if future.result() is not None:
        response = future.result()
        output = []
        for item in response.top_k_results:
            output.append({
                "id": item.node_id,
                "label": item.label,
                "distance": round(item.score, 2),   # Round to avoid decimal explosionm
                "pos": [round(p, 3) for p in item.position]
            })
        return json.dumps(output)
    else:
        return f"Error: {future.exception()}"