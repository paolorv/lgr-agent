#### SPAWN WAFFLE IN GAZEBO HARFMONIC #########

## Launch Empty World ##
# Source ROS 2 to get Gazebo paths
source /opt/ros/jazzy/setup.bash

# Launch GUI
gz sim -v 4 empty.sdf

## Spawn Wafflebot ##
# 1. Source ROS 2 (just in case)
source /opt/ros/jazzy/setup.bash

# 2. Tell Gazebo where the Turtlebot meshes are
export GZ_SIM_RESOURCE_PATH=/opt/ros/jazzy/share

# 3. Spawn the robot
python3.12 /opt/ros/jazzy/bin/ros2 run ros_gz_sim create \
  -world empty \
  -name turtlebot3 \
  -x 0.0 -y 0.0 -z 0.1 \
  -string "$(python3.12 /opt/ros/jazzy/bin/xacro /opt/ros/jazzy/share/turtlebot3_description/urdf/turtlebot3_waffle_pi.urdf)"


## Link Gazebo-ROS2 data topics ##
source /opt/ros/jazzy/setup.bash
python3.12 /opt/ros/jazzy/bin/ros2 run ros_gz_bridge parameter_bridge \
  /cmd_vel@geometry_msgs/msg/Twist@gz.msgs.Twist \
  /scan@sensor_msgs/msg/LaserScan@gz.msgs.LaserScan \
  /odom@nav_msgs/msg/Odometry@gz.msgs.Odometry \
  /tf@tf2_msgs/msg/TFMessage@gz.msgs.Pose_V



### ################# UPDATED ######################################################################
### START THE EMPTY WORLD:
export GZ_SIM_RESOURCE_PATH=/opt/ros/jazzy/share:/opt/ros/jazzy/share/turtlebot3_gazebo/models
gz sim -v 4 empty.sdf

BETTER!
ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py


### SPAWN THE TURTLEBOT:
export GZ_SIM_RESOURCE_PATH=/opt/ros/jazzy/share:/opt/ros/jazzy/share/turtlebot3_gazebo/models
python3.12 /opt/ros/jazzy/bin/ros2 run ros_gz_sim create \
  -world empty \
  -name turtlebot3 \
  -x 0.0 -y 0.0 -z 0.1 \
  -file /opt/ros/jazzy/share/turtlebot3_gazebo/models/turtlebot3_waffle_pi/model.sdf

### CHECK TOPICS FOR BOTH GAZEBO AND ROS2:
gz topic -l | grep vel

gz topic -e -t /cmd_vel
python3.12 /opt/ros/jazzy/bin/ros2 topic info /cmd_vel

### ONE-WAY BRIDGE:
# 1. Setup
deactivate 2>/dev/null || true
unset PYTHONPATH
source /opt/ros/jazzy/setup.bash

# 2. Run One-Way Bridge (ROS Twist -> Gazebo Twist)
python3.12 /opt/ros/jazzy/bin/ros2 run ros_gz_bridge parameter_bridge \
  "/cmd_vel@geometry_msgs/msg/Twist]gz.msgs.Twist" \
  "/scan@sensor_msgs/msg/LaserScan[gz.msgs.LaserScan" \
  "/odom@nav_msgs/msg/Odometry[gz.msgs.Odometry"

### RUN TELEOP
source /opt/ros/jazzy/setup.bash
export TURTLEBOT3_MODEL=waffle_pi
python3.12 /opt/ros/jazzy/lib/turtlebot3_teleop/teleop_keyboard
