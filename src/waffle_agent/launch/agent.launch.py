from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    # 1. Declare the 'streaming' argument
    streaming_arg = DeclareLaunchArgument(
        'streaming',
        default_value='false',
        description='Enable streaming mode'
    )

    # 2. Define the Node
    waffle_agent_node = Node(
        package='waffle_agent',
        # Note: In ROS 2, 'executable' is usually the entry point name defined 
        # in your setup.py, typically without the '.py' extension.
        executable='waffle_agent.py', 
        name='rosa_waffle_agent',
        output='screen',
        respawn=False,
        respawn_delay=10.0,
        parameters=[{
            'streaming': LaunchConfiguration('streaming')
        }]
        # Note: 'cwd="node"' is removed (see important note below)
    )

    return LaunchDescription([
        streaming_arg,
        waffle_agent_node
    ])