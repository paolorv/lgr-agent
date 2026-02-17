# Waffle Agent - ROS2 Jazzy Setup Guide

## Overview

This package has been migrated from ROS1 to **ROS2 Jazzy**. The `waffle_agent` is an embodied ROSA (Robot Operating System Agent) for the TurtleSim robot.

## Project Structure

```
waffle_agent/
├── CMakeLists.txt           # ROS2 build configuration (ament_cmake)
├── package.xml              # ROS2 package metadata (format="3")
├── setup.py                 # Python package installation
├── setup.cfg                # Python installation configuration
├── resource/                # ROS2 resource files
│   └── waffle_agent         # Package marker
├── waffle_agent/            # Python package directory
│   ├── __init__.py
│   └── scripts/
│       ├── __init__.py
│       └── waffle_agent.py  # Main agent node
├── scripts/                 # Original scripts (for reference)
│   ├── help.py
│   ├── llm.py
│   ├── prompts.py
│   ├── tools/
│   └── waffle_agent.py
└── launch/                  # ROS2 launch files
```

## Key Changes from ROS1 to ROS2

### 1. **Build System**
- Changed from `catkin` to `ament_cmake`
- `package.xml` format updated from 2 to 3
- Added `setup.py` for Python package management

### 2. **Initialization**
- **ROS1**: `rospy.init_node("node_name")`
- **ROS2**: `rclpy.init(args=args)` + `rclpy.create_node("node_name")`

### 3. **Parameter Handling**
- **ROS1**: `rospy.get_param("~param_name", default)`
- **ROS2**: `node.declare_parameter("param_name", default).value`

### 4. **Node Cleanup**
- Added proper shutdown with `node.destroy_node()` and `rclpy.shutdown()`

### 5. **ROSA Version**
- Updated from `ros_version=1` to `ros_version=2`

## Installation & Building

### Prerequisites

Ensure you have ROS2 Jazzy installed:

```bash
# Verify ROS2 Jazzy installation
echo $ROS_DISTRO  # Should output: jazzy
```

### Building the Package

```bash
# Navigate to your ROS2 workspace
cd ~/ros2_ws  # or your workspace path

# Build the package
colcon build --packages-select waffle_agent

# Source the workspace
source install/setup.bash
```

### Installation Method

The package uses **ament_python** for installation:

```bash
# The setup.py will install the package as an entry point:
ros2 run waffle_agent waffle_agent
```

Or directly:

```bash
python3 -m waffle_agent.scripts.waffle_agent
```

## Running the Node

### Basic Execution

```bash
# Method 1: Using ros2 run
ros2 run waffle_agent waffle_agent

# Method 2: Direct Python execution
python3 -m waffle_agent.scripts.waffle_agent
```

### With Parameters

```bash
# Enable streaming mode
ros2 run waffle_agent waffle_agent --ros-args -p streaming:=true
```

### Using Launch Files

```bash
ros2 launch waffle_agent waffle_agent.launch.py
```

## Dependencies

### Required ROS2 Packages
- `rclpy` - ROS2 Python client library
- `std_msgs` - Standard message types
- `std_srvs` - Standard service definitions

### Required Python Packages
- `langchain` - Language model framework
- `langchain-community` - Community language model implementations
- `langchain-openai` - OpenAI language models
- `langchain-ollama` - Ollama language models
- `rich` - Rich terminal formatting
- `python-dotenv` - Environment variable management
- `pyinputplus` - Enhanced input handling
- `rosa` - ROSA framework (local package)

## Configuration

### Environment Variables

Create a `.env` file in your workspace root:

```bash
# Example .env configuration
OPENAI_API_KEY=your_api_key_here
OLLAMA_BASE_URL=http://localhost:11434
```

### Parameters

The node accepts the following ROS2 parameters:

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `streaming` | bool | false | Enable streaming mode for responses |

## Troubleshooting

### Build Issues

**Problem**: `ament_cmake not found`
```bash
# Solution: Install ROS2 development tools
sudo apt install ros-jazzy-ament-cmake
```

**Problem**: Python import errors
```bash
# Solution: Ensure Python path includes package
export PYTHONPATH=$PYTHONPATH:install/lib/python3/dist-packages
```

### Runtime Issues

**Problem**: `ModuleNotFoundError: No module named 'rosa'`
```bash
# Solution: Ensure rosa package is in the workspace and built
colcon build --packages-select rosa
source install/setup.bash
```

**Problem**: `rclpy not found`
```bash
# Solution: Install rclpy
sudo apt install python3-rclpy
```

## File Organization Notes

⚠️ **Important**: The original scripts are kept in `scripts/` for reference. The actual package code is in the `waffle_agent/` directory:

- **Use**: `waffle_agent/scripts/waffle_agent.py` (package location)
- **Reference**: `scripts/waffle_agent.py` (original location)

If you make changes, update both locations or consolidate to one.

## Next Steps

1. **Copy helper modules** - Copy `help.py`, `llm.py`, `prompts.py` from `scripts/` to `waffle_agent/scripts/` if not already present
2. **Copy tools** - Move `tools/` package into `waffle_agent/tools/`
3. **Update imports** - Verify all imports in the main script work with the new package structure
4. **Create launch file** - Add ROS2 launch file in `launch/waffle_agent.launch.py`
5. **Test** - Run and verify all functionality works with ROS2 Jazzy

## Additional Resources

- [ROS2 Documentation](https://docs.ros.org/en/jazzy/)
- [rclpy API Reference](https://docs.ros.org/en/jazzy/p/rclpy/generated/rclpy.html)
- [Migration Guide from ROS1 to ROS2](https://docs.ros.org/en/jazzy/How-To-Guides/Migrating-from-ROS1.html)
