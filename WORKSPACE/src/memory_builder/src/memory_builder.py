import rospy
from geometry_msgs.msg import PoseWithCovarianceStamped
from std_msgs.msg import String
from scipy.spatial.transform import Rotation as R

from remembr.memory.memory import MemoryItem
from remembr.memory.milvus_memory import MilvusMemory

from common_utils import format_pose_msg


class MemoryBuilderNode:

    def __init__(self):

        rospy.init_node("MemoryBuilderNode")

        db_collection = rospy.get_param("~db_collection", "test_collection")
        db_ip = rospy.get_param("~db_ip", "127.0.0.1")

        pose_topic = rospy.get_param("~pose_topic", "/amcl_pose")
        caption_topic = rospy.get_param("~caption_topic", "/caption")

        rospy.Subscriber(pose_topic,
                         PoseWithCovarianceStamped,
                         self.pose_callback)

        rospy.Subscriber(caption_topic,
                         String,
                         self.caption_callback)

        self.memory = MilvusMemory(db_collection, db_ip)

        self.pose_msg = None

    def pose_callback(self, msg):
        self.pose_msg = msg

    def caption_callback(self, msg):
        if self.pose_msg is not None:
            position, angle, pose_time = format_pose_msg(self.pose_msg)

            memory = MemoryItem(
                caption=msg.data,
                time=pose_time,
                position=position,
                theta=angle
            )

            rospy.loginfo(f"Added memory item {memory}")
            self.memory.insert(memory)


if __name__ == "__main__":
    node = MemoryBuilderNode()
    rospy.spin()
