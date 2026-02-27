#!/usr/bin/env bash
# Copyright (c) 2024. Jet Propulsion Laboratory. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This script launches the ROSA demo in Docker

# Check if Docker is installed
if ! command -v docker &> /dev/null; then
    echo "Error: Docker is not installed. Please install Docker and try again."
    exit 1
fi

# Set default headless mode
HEADLESS=${HEADLESS:-false}
DEVELOPMENT=${DEVELOPMENT:-false}

# Enable X11 forwarding based on OS
case "$(uname)" in
    Linux*|Darwin*)
        echo "Enabling X11 forwarding..."
        # If running under WSL, use :0 for DISPLAY
        if grep -q "WSL" /proc/version 2>/dev/null; then
            export DISPLAY=:0
        else
            # Use existing DISPLAY if set, otherwise default to :1
            export DISPLAY=${DISPLAY:-:1}
        fi
        xhost +local:docker || xhost + || echo "Warning: xhost configuration failed, X11 may not work"
        ;;
    MINGW*|CYGWIN*|MSYS*)
        echo "Enabling X11 forwarding for Windows..."
        export DISPLAY=host.docker.internal:0
        ;;
    *)
        echo "Error: Unsupported operating system."
        exit 1
        ;;
esac

# Check if X11 forwarding is working
if ! xset q &>/dev/null; then
    echo "Warning: X11 forwarding may not be working properly."
    echo "Continuing anyway, but GUI applications might fail."
fi

# Build and run the Docker container
CONTAINER_NAME="rosa-ltm-test"

#echo "Building the $CONTAINER_NAME Docker image..."
#docker build --build-arg DEVELOPMENT=$DEVELOPMENT -t $CONTAINER_NAME -f Dockerfile . || { echo "Error: Docker build failed"; exit 1; }

echo "Running the Docker container..."

# Detect GPU and set appropriate flags
GPU_FLAGS=""
EXTRA_ENV=""

if command -v nvidia-smi &> /dev/null; then
    echo "Detected NVIDIA GPU via nvidia-smi"
    
    # Check if nvidia-container-runtime is available
    if docker info 2>/dev/null | grep -q "Runtimes:.*nvidia"; then
        echo "  ✓ NVIDIA Docker runtime detected"
        
        # --- FIX APPLIED HERE ---
        # Added '__NV_PRIME_RENDER_OFFLOAD=1' to explicitly enable 
        # PRIME offload for hybrid GPU setups (like laptops).
        GPU_FLAGS="--gpus all --runtime=nvidia"
        EXTRA_ENV="-e NVIDIA_VISIBLE_DEVICES=all -e NVIDIA_DRIVER_CAPABILITIES=all -e __GLX_VENDOR_LIBRARY_NAME=nvidia -e __NV_PRIME_RENDER_OFFLOAD=1"
        # ------------------------
        
    elif docker run --rm --gpus all nvidia/cuda:11.0-base nvidia-smi &>/dev/null; then
        echo "  ✓ Docker --gpus flag working"
        
        # --- FIX APPLIED HERE (Fallback) ---
        GPU_FLAGS="--gpus all"
        EXTRA_ENV="-e NVIDIA_VISIBLE_DEVICES=all -e NVIDIA_DRIVER_CAPABILITIES=all -e __GLX_VENDOR_LIBRARY_NAME=nvidia -e __NV_PRIME_RENDER_OFFLOAD=1"
        # -----------------------------------
        
    else
        echo "  ✗ NVIDIA Docker runtime not properly configured"
        echo "  Please install nvidia-container-toolkit:"
        echo "    sudo apt-get install -y nvidia-container-toolkit"
        echo "    sudo systemctl restart docker"
        echo "  Falling back to /dev/dri passthrough..."
        GPU_FLAGS="--device /dev/dri:/dev/dri"
    fi
elif [ -d /dev/dri ]; then
    echo "Detected /dev/dri — enabling generic GPU (Intel/AMD) passthrough"
    GPU_FLAGS="--device /dev/dri:/dev/dri"
    
    # Find DRI library path
    if [ -d /usr/lib/x86_64-linux-gnu/dri ]; then
        DRI_LIB_PATH="/usr/lib/x86_64-linux-gnu/dri"
    elif [ -d /usr/lib/dri ]; then
        DRI_LIB_PATH="/usr/lib/dri"
    else
        DRI_LIB_PATH=""
        echo "Warning: could not find host DRI driver folder."
    fi
    
    if [ -n "$DRI_LIB_PATH" ]; then
        GPU_FLAGS="$GPU_FLAGS -v ${DRI_LIB_PATH}:${DRI_LIB_PATH}:ro"
    fi
else
    echo "No GPU detected — running with software rendering"
    GPU_FLAGS=""
    EXTRA_ENV="-e LIBGL_ALWAYS_SOFTWARE=1"
fi

# Run the container
docker run -it --rm \
  $GPU_FLAGS \
  --name $CONTAINER_NAME \
  -e DISPLAY=$DISPLAY \
  -e XDG_RUNTIME_DIR=/tmp/runtime-root \
  -e LIBGL_ALWAYS_INDIRECT=0 \
  -e QT_X11_NO_MITSHM=1 \
  $EXTRA_ENV \
  -v /var/run/docker.sock:/var/run/docker.sock \
  -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
  -v "$PWD/src":/app/src \
  -v "$PWD/tests":/app/tests \
  -v "$PWD/.gazebo":/app/.gazebo \
  -v "$HOME/.gazebo/models":/root/.gazebo/models \
  -v "$HOME/.gazebo/worlds":/root/.gazebo/worlds \
  -v /mnt/1Tb-u/NaVQA_eval:/app/NaVQA_eval \
  --group-add video \
  --network host \
  --privileged \
  --shm-size=512m \
  $CONTAINER_NAME

# Disable X11 forwarding
xhost -local:docker || xhost - || echo "Warning: xhost cleanup failed"
