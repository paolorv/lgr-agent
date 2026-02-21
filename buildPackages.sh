# FIX NUMPY MISMATCH
#/usr/bin/python3 -m pip uninstall -y numpy scipy scikit-learn
# /usr/bin/python3 -m pip uninstall -y numpy scipy scikit-learn

# # 2. Clear pip cache so it doesn't accidentally reuse the corrupted 2.0 wheels
# /usr/bin/python3 -m pip cache purge

# # 3. Clean install the locked 1.x trio (bypassing cache just to be safe)
# /usr/bin/python3 -m pip install "numpy==1.26.4" "scipy==1.13.1" "scikit-learn==1.4.2" --no-cache-dir



# export ROS2_DISTRO=humble
# # Update and install required packages for jazzy
# #apt update && apt install -y \
# #    ros-${ROS2_DISTRO}-navigation2 \
# #    ros-${ROS2_DISTRO}-nav2-* \
# #    ros-${ROS2_DISTRO}-ros-gz \
# #    ros-${ROS2_DISTRO}-tf2-geometry-msgs \
# #    ros-${ROS2_DISTRO}-joint-state-publisher \
# #    ros-${ROS2_DISTRO}-pointcloud-to-laserscan \
# #    ros-${ROS2_DISTRO}-tf-transformations \
# #    ros-${ROS2_DISTRO}-joint-state-publisher-gui \
# #    ros-${ROS2_DISTRO}-joint-state-broadcaster \
# #    ros-${ROS2_DISTRO}-rmw-cyclonedds-cpp \
# #    xterm

# # Update and install required packages for humble
# #apt update && apt install -y \
# #    ros-${ROS2_DISTRO}-navigation2 \
# #    ros-${ROS2_DISTRO}-nav2-bringup \
# #    ros-${ROS2_DISTRO}-ros-gz \
# #    ros-${ROS2_DISTRO}-tf2-geometry-msgs \
# #    ros-${ROS2_DISTRO}-joint-state-publisher \
# #    ros-${ROS2_DISTRO}-pointcloud-to-laserscan \
# #    ros-${ROS2_DISTRO}-tf-transformations \
# #    ros-${ROS2_DISTRO}-joint-state-publisher-gui \
# #    ros-${ROS2_DISTRO}-joint-state-broadcaster \
# #    ros-${ROS2_DISTRO}-rmw-cyclonedds-cpp \
# #    xterm

# # Update and install required packages for humble
# apt update && apt install -y \
#     ros-${ROS2_DISTRO}-navigation2 \
#     ros-${ROS2_DISTRO}-nav2-bringup \
#     ros-${ROS2_DISTRO}-tf2-geometry-msgs \
#     ros-${ROS2_DISTRO}-joint-state-publisher \
#     ros-${ROS2_DISTRO}-pointcloud-to-laserscan \
#     ros-${ROS2_DISTRO}-tf-transformations \
#     ros-${ROS2_DISTRO}-joint-state-publisher-gui \
#     ros-${ROS2_DISTRO}-joint-state-broadcaster \
#     ros-${ROS2_DISTRO}-rmw-cyclonedds-cpp \
#     xterm

# /opt/venv/csagent/bin/pip install empy==3.3.4 lark
# /opt/venv/csagent/bin/pip install catkin_pkg lark

# export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
colcon build --base-paths src --symlink-install
source install/setup.bash