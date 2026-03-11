import os
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument, OpaqueFunction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration

def generate_launch_description():

    mode_arg = DeclareLaunchArgument(
        name="mode",
        default_value="slam",
        description="Launch SLAM or localization",
        choices=["slam", "localization"],
    )

    sim_arg = DeclareLaunchArgument(
        name="sim",
        default_value="true",
        description="Launch simulation with gazebo or launch real robot navigation",
        choices=["true", "false"],
    )

    map_arg = DeclareLaunchArgument(
        name="map",
        default_value="",
        description="Full path to map yaml file to load",
    )

    return LaunchDescription([
        mode_arg,
        sim_arg,
        map_arg,
        OpaqueFunction(function=launch_setup),
    ])


def launch_setup(context):

    # Nav2-related files
    nav2_launch_file = os.path.join(get_package_share_directory("nav2_bringup"), "launch", "bringup_launch.py")
    nav2_params_file = os.path.join(get_package_share_directory("agilex_scout_nav2"), "config", "slam_toolbox.yaml")

    # command-line parameters
    mode = LaunchConfiguration("mode").perform(context).lower()
    sim = LaunchConfiguration("sim").perform(context).lower()
    map_path = LaunchConfiguration("map").perform(context)

    # Strings required for the Nav2 bringup arguments
    slam = "True" if mode == "slam" else "False"
    use_sim_time = "True" if sim == "true" else "False"
    
    # Boolean required for the local node parameters to fix the RViz goal timestamp
    is_sim = (sim == "true")

    # Nav2 bringup
    nav2_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(nav2_launch_file),
        launch_arguments={
            "use_sim_time": use_sim_time,
            "params_file": nav2_params_file,
            "slam": slam,
            "map": map_path,
        }.items(),
    )

    # world->map static TF
    static_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        arguments=[
            "--x",              "0.0",
            "--y",              "0.0",
            "--z",              "0.0",
            "--yaw",            "0.0",
            "--pitch",          "0.0",
            "--roll",           "0.0",
            "--frame-id",       "world",
            "--child-frame-id", "map",
        ],
        parameters=[{"use_sim_time": is_sim}]
    )

    # RViz2
    rviz_default_config_file = os.path.join(get_package_share_directory("agilex_scout_nav2"), "rviz", "nav2.rviz")
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="screen",
        arguments=["-d", rviz_default_config_file],
        parameters=[{"use_sim_time": is_sim}]
    )

    return [
        nav2_launch,
        rviz_node,
        static_tf
    ]