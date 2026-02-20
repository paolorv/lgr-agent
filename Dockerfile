# ============================================================
#  Base image: ROS2 Humble (Python 3.10) → ROSA environment
# ============================================================
FROM osrf/ros:humble-desktop AS rosa-ros2
LABEL authors="Paolo Riva"

ENV DEBIAN_FRONTEND=noninteractive
ENV HEADLESS=false
ARG DEVELOPMENT=false

# --- ROS2 NAV2 config (requires the cyclonedds to be installed) ---
ENV RMW_IMPLEMENTATION=rmw_cyclonedds_cpp

# ------------------------------------------------------------
# Add Gazebo Harmonic (OSRF) apt repository
# ------------------------------------------------------------
RUN apt-get update && apt-get install -y curl lsb-release gnupg software-properties-common && \
    curl -sSL https://packages.osrfoundation.org/gazebo.gpg \
        -o /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] \
        https://packages.osrfoundation.org/gazebo/ubuntu-stable $(lsb_release -cs) main" \
        > /etc/apt/sources.list.d/gazebo-stable.list && \
    rm -rf /var/lib/apt/lists/*

# ------------------------------------------------------------
# System packages + Python 3.10 + ROS2 packages commonly needed
# ------------------------------------------------------------
RUN apt-get update && apt-get install -y --no-install-recommends \
    # Python 3.10 (Native for Ubuntu 22.04 / Humble)
    python3.10 python3.10-venv python3.10-dev \
    # ROS2 packages that exist in Humble
    #ros-humble-turtlesim \
    #ros-humble-turtlebot3-gazebo \
    #ros-humble-turtlebot3-teleop \
    #ros-humble-turtlebot3-description \
    # Gazebo Harmonic + ROS 2 bridge
    gz-harmonic \
    ros-humble-ros-gz \
    # ros2_control packages
    ros-humble-ros2-control \
    ros-humble-ros2-controllers \
    # essentials and GUI libraries
    locales mesa-utils mesa-utils-extra \
    libgl1-mesa-dri libglu1-mesa \
    # Additional GPU/Graphics support (Ubuntu 22.04 Jammy equivalents)
    libglvnd0 libglx0 libglvnd-dev libopengl0 \
    libegl1 libgles2 libegl-mesa0 \
    libvulkan1 vulkan-tools \
    mesa-vulkan-drivers \
    # X11 and display
    x11-apps xvfb \
    # Development tools
    cargo rustc tmux git nano docker.io \
    python3-pip python3-empy python3-defusedxml python3-colcon-common-extensions python3-flask \
    build-essential wget curl \
 && rm -rf /var/lib/apt/lists/*

# ============================================================
# Configure NVIDIA Container Runtime environment variables
# ============================================================
ENV NVIDIA_VISIBLE_DEVICES=all
ENV NVIDIA_DRIVER_CAPABILITIES=all
ENV __GLX_VENDOR_LIBRARY_NAME=nvidia

# ============================================================
# CUDA TOOLKIT INSTALL (Commented out as in original)
# ============================================================
# Define versions for easy updates
#ARG CUDA_MAJOR_VERSION=13
#ARG CUDA_MINOR_VERSION=0
# The apt package usually follows the format cuda-toolkit-X-Y
#ARG CUDA_PKG_VERSION=${CUDA_MAJOR_VERSION}-${CUDA_MINOR_VERSION}

#RUN wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-keyring_1.1-1_all.deb && \
#    sudo dpkg -i cuda-keyring_1.1-1_all.deb && \
#    sudo apt-get update && \
#    sudo apt-get -y install cuda-toolkit-${CUDA_PKG_VERSION}
### Check sintax

# ============================================================
# Create single Python 3.10 venv used by ROSA + REMEMBR
# ============================================================
RUN python3.10 -m venv /opt/venv/csagent && \
    /opt/venv/csagent/bin/python -m ensurepip && \
    /opt/venv/csagent/bin/pip install -U pip setuptools wheel

ENV PATH="/root/.cargo/bin:${PATH}"
ENV CSAGENT_ENV=/opt/venv/csagent

# ------------------------------------------------------------
# Useful environment variables for TurtleBot3 and workspace
# ------------------------------------------------------------
ENV TURTLEBOT3_MODEL=waffle_pi
ENV COLCON_DEFAULTS_FILE=/root/colcon_defaults.yaml

# Update root bashrc: source ros2 & venv and provide start alias
RUN echo "source /opt/ros/humble/setup.bash" >> /root/.bashrc && \
    echo "source /opt/venv/csagent/bin/activate" >> /root/.bashrc && \
    echo "alias start='colcon build --base-paths src --symlink-install --packages-select waffle_agent && source install/setup.bash && ros2 run waffle_agent agent --ros-args -p streaming:=False'" >> /root/.bashrc && \
    echo "export TURTLEBOT3_MODEL=${TURTLEBOT3_MODEL}" >> /root/.bashrc && \
    echo "export COLCON_DEFAULTS_FILE=${COLCON_DEFAULTS_FILE}" >> /root/.bashrc

# ============================================================
# rosdep initialization (allow re-run without failing)
# ============================================================
RUN rosdep init || true && rosdep update

# ============================================================
# Copy project into image
# ============================================================
COPY . /app/
WORKDIR /app/

# ============================================================
# Install ROSA and common Python deps (use venv pip)
# ============================================================
# Install ROSA: editable in dev, otherwise install from pip if available
RUN /bin/bash -lc '\
    if [ "$DEVELOPMENT" = "true" ]; then \
        /opt/venv/csagent/bin/pip install -e . ; \
    else \
        /opt/venv/csagent/bin/pip install -U jpl-rosa>=1.0.7 || true ; \
    fi'

# Install Waffle-agent dependencies globally to system Python 3.10
RUN /usr/bin/python3 -m pip install python-dotenv pyinputplus jpl-rosa rich langchain langchain-ollama requests

# ============================================================
# NEW REMEMBR + VILA installation (inside global python env)
# ============================================================
WORKDIR /app/remembr

# Upgrade pip and setuptools to fix the resolver AssertionError bug
RUN /usr/bin/python3 -m pip install --upgrade pip setuptools

# Install remembr in the core python env used by ROS2
RUN /usr/bin/python3 -m pip install -e .

# REMEMBR extra requirements
WORKDIR /app/remembr
# Install requirements, ignoring the system-installed sympy to avoid distutils uninstall errors
RUN /usr/bin/python3 -m pip install -r requirements.txt --no-cache-dir --ignore-installed sympy && \
    /usr/bin/python3 -m pip install --no-cache-dir "transformers==4.46.0" "peft==0.11.1" "sentence-transformers==2.7.0"

### ADDITIONAL FIXES
RUN /usr/bin/python3 -m pip install "setuptools==79.0.0"
RUN /usr/bin/python3 -m pip install -U langchain-core langchain-ollama langchain python-dotenv pyinputplus jpl-rosa rich requests

# ============================================================
# Helper script to activate the venv in a running container
# ============================================================
RUN echo '#!/bin/bash\nsource /opt/venv/csagent/bin/activate' > /app/use_csagent && \
    chmod +x /app/use_csagent

# Set working dir and default command: interactive shell with ROS2 + venv sourced
WORKDIR /app
CMD ["/bin/bash", "-c", "source /opt/ros/humble/setup.bash && source /opt/venv/csagent/bin/activate && echo 'ROSA+REMEMBR environment ready on ROS2 Humble with Python 3.10' && echo 'Run runwaffletester.sh to launch the Gazebo test environment, then run `start` to build and launch the rosa_waffle_bot controller.' && /bin/bash"]