from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    streaming_arg = DeclareLaunchArgument(
        'streaming', default_value='False',
        description='Enable streaming output for LLM'
    )

    waffle_agent_node = Node(
        package='waffle_agent',
        executable='agent',
        name='waffle_agent',
        output='screen',
        emulate_tty=True,  # Needed for Rich console output/colors
        parameters=[{
            'streaming': LaunchConfiguration('streaming')
        }]
    )

    return LaunchDescription([
        streaming_arg,
        waffle_agent_node
    ])