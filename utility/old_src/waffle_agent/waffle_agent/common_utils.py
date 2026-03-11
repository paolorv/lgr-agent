import numpy as np
from scipy.spatial.transform import Rotation as R
from nav_msgs.msg import Odometry

def format_pose_msg(msg: Odometry):

    position = np.array([
        msg.pose.pose.position.x,
        msg.pose.pose.position.y,
        msg.pose.pose.position.z
    ])

    quat = np.array([
        msg.pose.pose.orientation.x,
        msg.pose.pose.orientation.y,
        msg.pose.pose.orientation.z,
        msg.pose.pose.orientation.w
    ])

    # yaw angle
    yaw = R.from_quat(quat).as_euler('xyz')[2]

    # convert timestamp
    stamp = msg.header.stamp
    time = stamp.sec + stamp.nanosec * 1e-9

    return position, yaw, time