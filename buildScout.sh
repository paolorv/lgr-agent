apt-get install ros-jazzy-pointcloud-to-laserscan

colcon build --base-paths src --symlink-install
source install/setup.bash
ros2 launch simulation scout_sim.launch.py