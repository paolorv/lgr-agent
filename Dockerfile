# ============================================================
#  Base image: ROS2 Jazzy (Python 3.10) → ROSA environment
# ============================================================
FROM osrf/ros:jazzy-desktop-noble AS rosa-ros2
LABEL authors="Paolo Riva"

ENV DEBIAN_FRONTEND=noninteractive
ENV HEADLESS=false
ARG DEVELOPMENT=true

# ------------------------------------------------------------
# Add Gazebo Harmonic (OSRF) apt repository and deadsnakes PPA for Python 3.10
# ------------------------------------------------------------
RUN apt-get update && apt-get install -y curl lsb-release gnupg software-properties-common && \
    curl -sSL https://packages.osrfoundation.org/gazebo.gpg \
        -o /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] \
        https://packages.osrfoundation.org/gazebo/ubuntu-stable $(lsb_release -cs) main" \
        > /etc/apt/sources.list.d/gazebo-stable.list && \
    add-apt-repository -y ppa:deadsnakes/ppa && \
    rm -rf /var/lib/apt/lists/*

# ------------------------------------------------------------
# System packages + Python 3.10 + ROS2 packages commonly needed
# ------------------------------------------------------------
RUN apt-get update && apt-get install -y --no-install-recommends \
    # Python 3.10
    #python3.10 python3.10-venv python3.10-dev \
    # Python 3.12
    python3.12 python3.12-venv python3.12-dev \
    # ROS2 packages that exist in Jazzy
    ros-jazzy-turtlesim \
    ros-jazzy-turtlebot3-gazebo \
    ros-jazzy-turtlebot3-teleop \
    ros-jazzy-turtlebot3-description \
    # Gazebo Harmonic + ROS 2 bridge (correct package)
    gz-harmonic \
    ros-jazzy-ros-gz \
    # ros2_control packages (names are correct)
    ros-jazzy-ros2-control \
    ros-jazzy-ros2-controllers \
    # essentials and GUI libraries
    locales mesa-utils mesa-utils-extra \
    libgl1-mesa-dri libglu1-mesa \
    # Additional GPU/Graphics support (Ubuntu 24.04 Noble)
    libglvnd0 libglx0 libglvnd-dev libopengl0 \
    libegl1 libgles2 libegl-mesa0 \
    libvulkan1 vulkan-tools \
    mesa-vulkan-drivers \
    # X11 and display
    x11-apps xvfb \
    # Development tools
    cargo rustc tmux git nano docker.io \
    python3-pip python3-empy python3-defusedxml python3-colcon-common-extensions \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# ============================================================
# Configure NVIDIA Container Runtime environment variables
# ============================================================
ENV NVIDIA_VISIBLE_DEVICES=all
ENV NVIDIA_DRIVER_CAPABILITIES=all
ENV __GLX_VENDOR_LIBRARY_NAME=nvidia

# ============================================================
# Create single Python 3.10 venv used by ROSA + REMEMBR
# ============================================================
RUN python3.12 -m venv /opt/venv/csagent && \
    /opt/venv/csagent/bin/python -m ensurepip && \
    /opt/venv/csagent/bin/pip install -U pip setuptools wheel

ENV PATH="/root/.cargo/bin:${PATH}"
ENV CSAGENT_ENV=/opt/venv/csagent

# Ensure python3 points to python3.10
RUN update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.12 1

# ------------------------------------------------------------
# Useful environment variables for TurtleBot3 and workspace
# ------------------------------------------------------------
ENV TURTLEBOT3_MODEL=waffle_pi
ENV COLCON_DEFAULTS_FILE=/root/colcon_defaults.yaml

# Update root bashrc: source ros2 & venv and provide start alias
RUN echo "source /opt/ros/jazzy/setup.bash" >> /root/.bashrc && \
    echo "source /opt/venv/csagent/bin/activate" >> /root/.bashrc && \
    echo "alias start='colcon build --symlink-install && source install/setup.bash && ros2 launch waffle_agent agent.launch'" >> /root/.bashrc && \
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
RUN /opt/venv/csagent/bin/pip install -U python-dotenv empy

# Install ROSA: editable in dev, otherwise install from pip if available
RUN /bin/bash -lc '\
    if [ "$DEVELOPMENT" = "true" ]; then \
        /opt/venv/csagent/bin/pip install -e . ; \
    else \
        # If jpl-rosa is available for Python 3.10 you can install it here, otherwise keep source copy in the image
        /opt/venv/csagent/bin/pip install -U jpl-rosa>=1.0.7 || true ; \
    fi'

# ============================================================
# REMEMBR + VILA installation (inside same venv)
# ============================================================
#WORKDIR /app/remembr

# Install REMEMBR base (editable)
#RUN /opt/venv/csagent/bin/pip install -e .

# Create deps and install VILA + flash-attn wheel (adjust wheel URL if needed)
#RUN mkdir -p deps && cd deps && \
#    git clone https://github.com/NVlabs/VILA.git && \
#    cd VILA && \
#    /opt/venv/csagent/bin/pip install --no-cache-dir https://github.com/Dao-AILab/flash-attention/releases/download/v2.5.8/flash_attn-2.5.8+cu122torch2.3cxx11abiFALSE-cp310-cp310-linux_x86_64.whl || true && \
#    /opt/venv/csagent/bin/pip install -e . && \
#    /opt/venv/csagent/bin/pip install -e ".[train]" && \
#    /opt/venv/csagent/bin/pip install -e ".[eval]" && \
#    /opt/venv/csagent/bin/pip install -U "transformers==4.46.0"

# REMEMBR extra requirements (pin transformers once, avoid conflicting downgrades)
#WORKDIR /app/remembr
#RUN /opt/venv/csagent/bin/pip install -r requirements.txt --no-cache-dir && \
#    /opt/venv/csagent/bin/pip install --no-cache-dir "transformers==4.46.0" "peft==0.11.1" "sentence-transformers==2.7.0" && \
#    /opt/venv/csagent/bin/pip install --no-cache-dir flask

# ============================================================
# Helper script to activate the venv in a running container
# ============================================================
RUN echo '#!/bin/bash\nsource /opt/venv/csagent/bin/activate' > /app/use_csagent && \
    chmod +x /app/use_csagent

# Set working dir and default command: interactive shell with ROS2 + venv sourced
WORKDIR /app
CMD ["/bin/bash", "-c", "source /opt/ros/jazzy/setup.bash && source /opt/venv/csagent/bin/activate && echo 'ROSA+REMEMBR environment ready on ROS2 Jazzy with Python 3.10' && echo 'Run runwaffletester.sh to launch the Gazebo test environment, then run `start` to build and launch the rosa_waffle_bot controller.' && /bin/bash"]

