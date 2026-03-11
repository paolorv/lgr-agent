import rclpy
from rclpy.node import Node
#from geometry_msgs.msg import PoseWithCovarianceStamped
from nav_msgs.msg import Odometry
from std_msgs.msg import String
from scipy.spatial.transform import Rotation as R
from remembr.memory.memory import MemoryItem
from remembr.memory.milvus_memory import MilvusMemory

from waffle_agent.common_utils import format_pose_msg

# GRAPHICS
from datetime import datetime
from collections import deque
from rich.live import Live
from rich.table import Table


class MemoryBuilderNode(Node):

    def __init__(self):
        super().__init__("MemoryBuilderNode")

        self.declare_parameter("db_collection", "test_collection")
        self.declare_parameter("db_ip", "127.0.0.1")

        self.declare_parameter("pose_topic", "/odom")
        self.declare_parameter("caption_topic", "/captions")

        self.pose_subscriber = self.create_subscription(
            Odometry,
            self.get_parameter("pose_topic").value,
            self.pose_callback,
            10
        )

        self.caption_subscriber = self.create_subscription(
            String,
            self.get_parameter("caption_topic").value,
            self.caption_callback,
            10
        )
        self.memory = MilvusMemory(
            self.get_parameter("db_collection").value,
            self.get_parameter("db_ip").value
        )

        self.pose_msg = None
        self.caption_msg = None
        self.logger = self.get_logger()

        # Store the last 15 events to display in the live table
        self.events = deque(maxlen=1)

        self.memory.reset()
        # This logger is safe because it runs before the Live table starts
        self.logger.info(f"MEMORY RESET SUCCESSFUL.\n\n\n\n\n\n\n\n\n\n\n\n")


    def pose_callback(self, msg: Odometry):
        self.pose_msg = msg
        #self.logger.info("Received pose message (MARKPOSE)")


    def caption_callback(self, msg: String):

        if self.pose_msg is None:
            # Use rich console print to avoid breaking the table if it fires
            if hasattr(self, 'live'):
                self.live.console.print("[yellow]Warning: No pose message received yet; cannot create memory item.[/yellow]")
            else:
                self.logger.warning("No pose message received yet; cannot create memory item.")
            return

        # Extract info from the odometry message
        position, angle, pose_time = format_pose_msg(self.pose_msg)
        # self.logger.info("MARK1 (pose formatted)") # Commented out to protect table

        # For the table visualization
        current_pose = (position[0], position[1], angle)

        memory_item = MemoryItem(
            caption=msg.data,
            time=pose_time,
            position=position,
            theta=angle
        )

        # self.logger.info("MARK2 (created MemoryItem)") # Commented out to protect table

        try:
            self.memory.insert(memory_item)
            # self.logger.info(f"ADDED MEMORY ITEM {memory_item}") # Commented out to protect table
            
            # Add to Rich Table
            self.record_event("INSERT", msg.data, current_pose)
            
        except Exception as e:
            if hasattr(self, 'live'):
                self.live.console.print(f"[red]Failed to insert memory: {e}[/red]")
            else:
                self.logger.error(f"Failed to insert memory: {e}")

    ## RICH CONSOLE METHODS
    def generate_table(self) -> Table:
        """Dynamically generates a rich Table based on the stored events."""
        table = Table(
            show_header=True, 
            header_style="bold white", 
            title="Milvus Memory Builder Events"
        )
        
        table.add_column("Action", style="bold", width=10)
        table.add_column("Date", justify="left", style="dim")
        table.add_column("Caption", justify="left", style="cyan")
        table.add_column("Pose (x, y, yaw)", justify="right", style="green")

        for action, date_str, caption, pose_str in self.events:
            if action == "INSERT":
                action_fmt = "[blue][INSERT][/blue]"
            else:
                action_fmt = f"[yellow][{action}][/yellow]"
                
            table.add_row(action_fmt, date_str, caption, pose_str)

        return table

    def record_event(self, action: str, caption: str, pose: tuple):
        """Records an event and triggers a Live display update."""
        date_str = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        pose_str = f"({pose[0]:.2f}, {pose[1]:.2f}, {pose[2]:.2f})"
        
        self.events.append((action, date_str, caption, pose_str))
        
        # If the live display is active, update it with the new table
        if hasattr(self, 'live'):
            self.live.update(self.generate_table())


def main(args=None):
    rclpy.init(args=args)
    node = MemoryBuilderNode()
    
    # Start the Live context manager. refresh_per_second=4 keeps it fluid.
    with Live(node.generate_table(), refresh_per_second=4) as live:
        # Assign the live instance to the node so it can trigger updates
        node.live = live
        
        try:
            rclpy.spin(node)
        except KeyboardInterrupt:
            pass
        finally:
            node.destroy_node()
            rclpy.shutdown()

if __name__ == '__main__':
    main()