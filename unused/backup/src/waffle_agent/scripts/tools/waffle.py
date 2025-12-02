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
