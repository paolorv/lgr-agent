cd /app/
export TURTLEBOT3_MODEL=waffle
export GZ_SIM_RESOURCE_PATH=/opt/ros/jazzy/share:/opt/ros/jazzy/share/turtlebot3_gazebo/models

# Bridge /cmd_vel topic between ROS2 and Gazebo
ros2 run ros_gz_bridge parameter_bridge \
  /cmd_vel@geometry_msgs/msg/Twist@gz.msgs.Twist &

# Launch Gazebo Harmonic with TurtleBot3 in a house environment
ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py

## Optional: launch teleop 
# ros2 run turtlebot3_teleop teleop_keyboard