import os
from ament_index_python.packages import get_package_share_directory
from math import pi

from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import Command
from launch.actions import SetEnvironmentVariable, ExecuteProcess


def generate_launch_description():

	# environmental variables for Gazebo
	set_env_vars_gz = [
		SetEnvironmentVariable(
			name="GZ_SIM_RESOURCE_PATH",
			value=os.environ.get("GZ_SIM_RESOURCE_PATH", "")
				+ ":" + os.path.join(get_package_share_directory("gazebo_worlds"), "agri")
		)
	]

	# Gazebo world launch
	gz_sim = ExecuteProcess(
		cmd=[
			"gz sim",
			"--verbose 4 -r",
			get_package_share_directory("gazebo_worlds"), "agri", "open_field_world.sdf",
		],
		output="log",
		shell=True,
	)

	# ROS 2 <-> Gazebo bridge
	ros2_gz_bridge_file = os.path.join(
		get_package_share_directory("simulation"),
		"config",
		"ros2_gz_bridge_config.yaml",
	)
	ros2_gz_bridge_node = Node(
		name="ros2_gz_bridge",
		package="ros_gz_bridge",
		executable="parameter_bridge",
		parameters=[
			{
				"config_file": ros2_gz_bridge_file,
				"qos_overrides./tf_static.publisher.durability": "transient_local",
				"use_sim_time": True,
			}
		],
		output="screen",
	)

	# robot description
	robot_description_file = os.path.join(
			get_package_share_directory('agilex_scout_description'),
			'urdf',
			'robot.urdf.xacro'
	)
	robot_description_param = {
		'robot_description': ParameterValue(
			Command([
				'xacro ',
				robot_description_file,
    			" odometry_source:=ground_truth",	# or 'encoders'
				" sim:=true",
			]),
			value_type=str
		)
	}

	# robot state publisher node
	robot_state_publisher_node = Node(
		package='robot_state_publisher',
		executable='robot_state_publisher',
		name='robot_state_publisher',
		output='screen',
		parameters=[{"use_sim_time": True}, robot_description_param],
		remappings=[
			("/joint_states", "/scout/joint_states"),
			("/robot_description", "/scout/robot_description"),
		],
	)

	# robot spawn in Gazebo
	spawn_robot_urdf_node = Node(
		name="spawn_robot_urdf",
		package="ros_gz_sim",
		executable="create",
		arguments=[
			"-name", "scout_v2",
			"-topic", "/scout/robot_description",
			"-x", "0",
			"-y", "0",
			"-z", "0.2346",
			"-R", "0",
			"-P", "0",
			"-Y", "0",
		],
		output="screen",
		parameters=[
			{
				'use_sim_time': True,
				'verbose': True
			},
		]
	)

	# RViz
	rviz_config_path = os.path.join(
		get_package_share_directory("simulation"),
		"rviz",
		"scout_sim.rviz",
	)
	rviz_node = Node(
		package="rviz2",
		executable="rviz2",
		arguments=["-d", rviz_config_path],
		parameters=[{"use_sim_time": True}]
	)

	# world->map static transform
	static_tf = Node(
		package="tf2_ros",
		executable="static_transform_publisher",
		arguments=[
			"--x", "0.0",
			"--y", "0.0",
			"--z", "0.0",
			"--yaw", "0.0",
			"--pitch", "0.0",
			"--roll", "0.0",
			"--frame-id", "world",
			"--child-frame-id", "map",
		],
		parameters=[{"use_sim_time": True}]
	)

	# simulate robot remote control
	teleop_keyboard_node = Node(
		name="teleop",
		package="teleop_twist_keyboard",
		executable="teleop_twist_keyboard",
		output="screen",
		prefix="xterm -e",
	)

	# compress the 3d point clouds into 2d scans for usage in Nav2
	pointcloud_to_laserscan_node = Node(
		package='pointcloud_to_laserscan',
		executable='pointcloud_to_laserscan_node',
		name='pointcloud_to_laserscan_node',
		remappings=[('cloud_in', "/points"),
					('scan', "/laser_scan")],
		parameters=[{
			'use_sim_time': True,
			'transform_tolerance': 0.05,
			'min_height': 0.0,
			'max_height': 1.0,
			'angle_min': -pi,
			'angle_max': pi,
			'angle_increment': pi / 180.0 / 2.0,
			'scan_time': 1/10, # 10Hz
			'range_min': 0.1,
			'range_max': 100.0,
			'use_inf': True,
		}],
	)

	return LaunchDescription(
		[
			static_tf,
			robot_state_publisher_node,
			*set_env_vars_gz,
			gz_sim,
			spawn_robot_urdf_node,
			ros2_gz_bridge_node,
			rviz_node,
			teleop_keyboard_node,
			pointcloud_to_laserscan_node
		]
	)