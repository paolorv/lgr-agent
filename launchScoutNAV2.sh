export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
source install/setup.bash
ros2 launch agilex_scout_nav2 navigation.launch.py sim:=true mode:=slam