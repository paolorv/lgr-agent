import rclpy
from rclpy.node import Node
#from geometry_msgs.msg import PoseWithCovarianceStamped
from nav_msgs.msg import Odometry
from std_msgs.msg import String
from scipy.spatial.transform import Rotation as R
from remembr.memory.memory import MemoryItem
from remembr.memory.milvus_memory import MilvusMemory

from waffle_agent.common_utils import format_pose_msg


class MemoryBuilderNode(Node):

    def __init__(self):
        super().__init__("MemoryBuilderNode")

        self.declare_parameter("db_collection", "test_collection")
        self.declare_parameter("db_ip", "127.0.0.1")

        self.declare_parameter("pose_topic", "/odometry")
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

        self.memory.reset()
        self.logger.info(f"MEMORY RESET SUCCESSFUL.")

    def pose_callback(self, msg: Odometry):
        self.pose_msg = msg
        #self.logger.info("Received pose message (MARKPOSE)")


    def caption_callback(self, msg: String):

        if self.pose_msg is None:
            self.logger.warning("No pose message received yet; cannot create memory item.")
            return

        # Extract info from the odometry message
        position, angle, pose_time = format_pose_msg(self.pose_msg)
        #self.logger.info("MARK1 (pose formatted)")

        memory_item = MemoryItem(
            caption=msg.data,
            time=pose_time,
            position=position,
            theta=angle
        )

        #self.logger.info("MARK2 (created MemoryItem)")

        try:
            self.memory.insert(memory_item)
            self.logger.info(f"ADDED MEMORY ITEM {memory_item}")
        except Exception as e:
            self.logger.error(f"Failed to insert memory: {e}")

def main(args=None):
    rclpy.init(args=args)
    node = MemoryBuilderNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()