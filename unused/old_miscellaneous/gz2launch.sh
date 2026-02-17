#!/usr/bin/env bash
set -euo pipefail

echo "===== Starting ROS 2 + Gazebo Harmonic test script ====="

# ------------------------------------------------------------
# Source ROS 2 Jazzy setup safely (avoid unbound variable errors)
# ------------------------------------------------------------
set +u
source /opt/ros/jazzy/setup.bash
set -u

# ------------------------------------------------------------
# Activate Python virtual environment
# ------------------------------------------------------------
source /opt/venv/csagent/bin/activate

# Upgrade Python dependencies
pip install --upgrade defusedxml

# ------------------------------------------------------------
# Setup ROS 2 workspace
# ------------------------------------------------------------
WORKSPACE="/app/ros2_ws"
SRC="$WORKSPACE/src"
mkdir -p "$SRC"
cd "$SRC"

# No external repos needed — using default Gazebo empty world
cd "$WORKSPACE"

# ------------------------------------------------------------
# Set TurtleBot3 model
# ------------------------------------------------------------
export TURTLEBOT3_MODEL=waffle_pi

# ------------------------------------------------------------
# Create ROS 2 launch directory and file
# ------------------------------------------------------------
LAUNCH_DIR="$SRC/launch"
mkdir -p "$LAUNCH_DIR"
LAUNCH_FILE="$LAUNCH_DIR/waffle_empty_world_launch.py"

cat << 'EOF' > "$LAUNCH_FILE"
from launch import LaunchDescription
from launch.actions import ExecuteProcess, TimerAction

def generate_launch_description():
    # Default Gazebo empty world
    world_file = '/usr/share/gazebo-11/worlds/empty.world'

    # Start Gazebo Harmonic
    start_gz = ExecuteProcess(
        cmd=['gz', 'sim', '--verbose', world_file],
        output='screen'
    )

    # Spawn TurtleBot3 after 3 seconds
    spawn_tb3 = TimerAction(
        period=3.0,
        actions=[
            ExecuteProcess(
                cmd=[
                    'ros2', 'run', 'ros_gz_sim', 'create',
                    '--name', 'turtlebot3',
                    '--file', '/opt/ros/jazzy/share/turtlebot3_description/urdf/turtlebot3_waffle_pi.urdf',
                    '--x', '0', '--y', '0', '--z', '0.1'
                ],
                output='screen'
            )
        ]
    )

    ld = LaunchDescription()
    ld.add_action(start_gz)
    ld.add_action(spawn_tb3)
    return ld
EOF

echo "Launch file created at $LAUNCH_FILE"

# ------------------------------------------------------------
# Build workspace (safe, no ROS1/catkin packages)
# ------------------------------------------------------------
colcon build --symlink-install || true

# Source workspace safely (avoid COLCON_TRACE unbound variable)
set +u
source install/setup.bash
set -u

# ------------------------------------------------------------
# Launch TurtleBot3 in Gazebo Harmonic empty world
# ------------------------------------------------------------
ros2 launch launch/waffle_empty_world_launch.py
