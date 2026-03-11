import time
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import requests
from datetime import datetime, timezone

# --- FIXED IMPORT FOR LANGCHAIN 0.3 ---
from langchain_core.tools import tool
# ---------------------------------------
#It was:
#from langchain.agents import tool, Tool

# GRAPH-SEARCH NECESSARY
import json
import ast
# Import the services so we can create the clients
from waffle_agent_msgs.srv import SearchByLabel, SearchByPosition, SearchByTime
from datetime import datetime, timezone

# NAV2 NECESSARY
import math
from rclpy.action import ActionClient
from nav2_msgs.action import NavigateToPose
from geometry_msgs.msg import PoseStamped


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

#@tool
#def move_waffle(linear: float = 0.2, angular: float = 0.0, duration: float = 2.0):
#    """Move the TurtleBot3 Waffle with given linear and angular velocities."""
#    if NODE is None:
#        return "Error: ROS Node not initialized in tools."

#    vel = Twist()
#    vel.linear.x = float(linear)
#    vel.angular.z = float(angular)
#    
#    rate_hz = 10
#    start_time = NODE.get_clock().now().nanoseconds
#    duration_ns = duration * 1e9
    
#    NODE.get_logger().info(f"Moving: lin={linear}, ang={angular}, dur={duration}")

#    while (NODE.get_clock().now().nanoseconds - start_time) < duration_ns:
#        CMD_VEL_PUB.publish(vel)
#        time.sleep(1.0 / rate_hz) 
    
#    CMD_VEL_PUB.publish(Twist())  # stop
#    return f"Moved with linear={linear}, angular={angular} for {duration} sec."

@tool
def get_robot_pose():
    """Get the robot's current position from odometry."""
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

   query = "The robot is currently requesting: " + query 

   if NODE:
       NODE.get_logger().info(f"Querying LTM with: '{query}'")

   try:
       resp = requests.post("http://localhost:8000/query", json={"query": query}, timeout=100)
       if resp.status_code != 200:
           return f"Error from Remembr server: {resp.text}"
       data = resp.json()
       pos = data.get("position")
       if pos: ## POSITIONAL QUERIES
           if NODE: NODE.get_logger().info(f"The Retrieved position was: '{pos}'")
           return f"Memory query successful. Location: {data['text']}. Position: [x={pos[0]:.2f}, y={pos[1]:.2f}, z={pos[2]:.2f}]."
       else:
           if NODE: NODE.get_logger().info(f"No position found. Details: '{data['text']}'")
           return f"Memory query successful. Details: {data['text']}"
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
    

# @tool
# def query_graph_memory_by_time(query: str) -> str:
#     """
#     Queries the robot's graph memory for nodes seen closest to a specific time.

#     Input formats accepted:
#       - "hh,mm,ss"       e.g. "14,30,00"  (today's date assumed, local time)
#       - "hh:mm:ss"       e.g. "14:30:00"  (today's date assumed, local time)
#       - Unix timestamp   e.g. "1720000000.5"
#       - "now"            uses the current time

#     Returns nodes sorted by how close their last-seen time is to the query,
#     with 'distance' being the time delta in seconds.
#     """
#     global NODE
#     if NODE is None:
#         return "Error: ROS Node not initialized."

#     # --- Parse the input into a Unix timestamp (float) ---
#     query_time_sec: float

#     query = query.strip()

#     if query.lower() == "now":
#         query_time_sec = time.time()

#     else:
#         # Try raw numeric (Unix epoch) first
#         try:
#             query_time_sec = float(query)

#         except ValueError:
#             # Normalize separators: "14,30,00" -> "14:30:00"
#             normalized = query.replace(",", ":")

#             try:
#                 # Parse as today + given time, in local timezone
#                 t = datetime.strptime(normalized, "%H:%M:%S")
#                 now = datetime.now()
#                 dt = now.replace(
#                     hour=t.hour,
#                     minute=t.minute,
#                     second=t.second,
#                     microsecond=0
#                 )
#                 query_time_sec = dt.timestamp()

#             except ValueError:
#                 return (
#                     f"Error: Could not parse time '{query}'. "
#                     "Use 'hh,mm,ss', 'hh:mm:ss', a Unix timestamp, or 'now'."
#                 )

#     NODE.get_logger().info(f"Time search: query_time_sec={query_time_sec:.2f}")

#     # --- Call the ROS2 service ---
#     client = NODE.create_client(SearchByTime, 'search_by_time')
#     if not client.wait_for_service(timeout_sec=1.0):
#         return "Error: Time Search Graph Service is offline."

#     req = SearchByTime.Request()
#     req.query_time_sec = query_time_sec
#     req.top_k = 0  # Use server default

#     future = client.call_async(req)
#     rclpy.spin_until_future_complete(NODE, future)

#     if future.result() is None:
#         return f"Error: {future.exception()}"

#     response = future.result()
#     output = []
#     for item in response.top_k_results:
#         output.append({
#             "id":       item.node_id,
#             "label":    item.label,
#             "delta_sec": round(item.score, 3),   # How many seconds off from query time
#             "pos":      [round(p, 3) for p in item.position]
#         })

#     return json.dumps(output)



@tool
def query_graph_memory_by_time(query: str):
    """
    Queries the robot's graph memory for nodes seen near a specific time.
    Input: A string representing the date and time, formatted exactly like 'YYYY-MM-DD HH:MM:SS' (e.g. '2023-01-16 15:55:32').
    """
    global NODE
    if NODE is None:
        return "Error: ROS Node not initialized."

    # 1. Let Python handle the complex epoch math safely
    try:
        # Parse the string into a datetime object
        dt_obj = datetime.strptime(query.strip(), '%Y-%m-%d %H:%M:%S')
        # Assume UTC to prevent local timezone shifts
        dt_obj = dt_obj.replace(tzinfo=timezone.utc)
        query_time_sec = dt_obj.timestamp()
    except ValueError:
        return "Error: Input must be a date/time string formatted exactly as 'YYYY-MM-DD HH:MM:SS'."

    # Create Client
    client = NODE.create_client(SearchByTime, 'search_by_time')
    if not client.wait_for_service(timeout_sec=1.0):
        return "Error: Temporal Graph Service is offline."

    # Build Request + Call service
    req = SearchByTime.Request()
    req.query_time = float(query_time_sec)  # Pass the safely computed float
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
                "time_difference_seconds": round(item.score, 2), # Typically score is the time delta
                "pos": [round(p, 3) for p in item.position]
            })
        return json.dumps(output)
    else:
        return f"Error: {future.exception()}"


@tool
def navigate_to_position(x: float, y: float, theta: float = 0.0) -> str:
    """
    Sends a Nav2 goal to navigate the robot to a specific x, y coordinate and yaw (theta) angle.
    Wait for the navigation to finish before returning.
    """
    global NODE
    if NODE is None:
        return "Error: ROS Node not initialized."

    # 1. Create the Action Client
    nav_to_pose_client = ActionClient(NODE, NavigateToPose, 'navigate_to_pose')

    NODE.get_logger().info("Waiting for Nav2 action server...")
    if not nav_to_pose_client.wait_for_server(timeout_sec=5.0):
        return "Error: Nav2 NavigateToPose action server not available."

    # 2. Construct the Goal message
    goal_msg = NavigateToPose.Goal()
    goal_msg.pose.header.frame_id = 'map'
    goal_msg.pose.header.stamp = NODE.get_clock().now().to_msg()

    goal_msg.pose.pose.position.x = float(x)
    goal_msg.pose.pose.position.y = float(y)
    goal_msg.pose.pose.position.z = 0.0

    # Convert theta (yaw) to quaternion
    goal_msg.pose.pose.orientation.x = 0.0
    goal_msg.pose.pose.orientation.y = 0.0
    goal_msg.pose.pose.orientation.z = math.sin(theta / 2.0)
    goal_msg.pose.pose.orientation.w = math.cos(theta / 2.0)

    NODE.get_logger().info(f"Sending Nav2 goal: x={x}, y={y}, theta={theta}")

    # 3. Send the Goal
    send_goal_future = nav_to_pose_client.send_goal_async(goal_msg)

    # Wait for the server to accept or reject the goal
    rclpy.spin_until_future_complete(NODE, send_goal_future)

    goal_handle = send_goal_future.result()
    if not goal_handle.accepted:
        return "Nav2 Goal was rejected by the action server."

    NODE.get_logger().info("Goal accepted, robot is moving. Waiting for result...")
    
    # 4. Wait for the robot to finish moving
    get_result_future = goal_handle.get_result_async()
    rclpy.spin_until_future_complete(NODE, get_result_future)

    result = get_result_future.result()
    
    # Action statuses: 4 is SUCCEEDED, 5 is CANCELED, 6 is ABORTED
    if result.status == 4:
        return f"Navigation successful. Robot reached x={x}, y={y}, theta={theta}."
    else:
        return f"Navigation failed or was aborted. Action status code: {result.status}"