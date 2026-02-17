# Do not run this script.
# It is automatically loaded and run by the Dockerfile.

export ROS2_DISTRO=jazzy
# Update and install required packages
apt update && apt install -y \
    ros-${ROS2_DISTRO}-navigation2 \
    ros-${ROS2_DISTRO}-nav2-* \
    ros-${ROS2_DISTRO}-ros-gz \
    ros-${ROS2_DISTRO}-tf2-geometry-msgs \
    ros-${ROS2_DISTRO}-joint-state-publisher \
    ros-${ROS2_DISTRO}-pointcloud-to-laserscan \
    ros-${ROS2_DISTRO}-tf-transformations \
    ros-${ROS2_DISTRO}-joint-state-publisher-gui \
    ros-${ROS2_DISTRO}-joint-state-broadcaster
