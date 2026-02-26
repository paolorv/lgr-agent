#!/bin/bash
set -e

# --- 1. FIX THE CUDA TOOLKIT MISMATCH ---
# Your Host Driver (Kernel) handles the RTX 5070. 
# The Container Toolkit (Userspace) must match PyTorch (CUDA 12).
echo "Downgrading Container Toolkit to 12.4 (Host Driver remains untouched)..."

# Remove the problematic CUDA 13 toolkit
apt-get -y remove cuda-toolkit-13-0
apt-get -y autoremove

# Install CUDA 12.4 Toolkit (compatible with Ubuntu 24.04)
wget -qO /tmp/cuda-keyring.deb https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2404/x86_64/cuda-keyring_1.0-1_all.deb
dpkg -i /tmp/cuda-keyring.deb
apt-get update
apt-get -y install --no-install-recommends cuda-toolkit-12-4

# Update Environment Variables for the new Toolkit
export CUDA_HOME=/usr/local/cuda-12.4
export PATH=${CUDA_HOME}/bin:${PATH}
export LD_LIBRARY_PATH=${CUDA_HOME}/lib64:${LD_LIBRARY_PATH}

# --- 2. INSTALL PYTORCH FOR VILA ---
# VILA requires Torch 2.3. We force re-install to ensure clean state.
echo "Installing PyTorch 2.3.0..."
/usr/bin/python3 -m pip install torch==2.3.0 torchvision==0.18.0 torchaudio==2.3.0 --index-url https://download.pytorch.org/whl/cu121 --break-system-packages



#############################################

# --- 3. BUILD FLASH ATTENTION ---
echo "Building Flash Attention..."
/usr/bin/python3 -m pip install packaging ninja psutil setuptools wheel --break-system-packages

# Clone specific version
rm -rf flash-attention
git clone https://github.com/Dao-AILab/flash-attention.git
cd flash-attention
git checkout v2.5.8
git submodule update --init --recursive

# BUILD FLAGS
export MAX_JOBS=4
export FLASH_ATTENTION_FORCE_BUILD=TRUE
# TARGET ARCH: 
# We build for Hopper (9.0) and include PTX. 
# The RTX 5070 driver will JIT compile this PTX at runtime.
export TORCH_CUDA_ARCH_LIST="8.0 8.6 8.9 9.0+PTX"

# Install
/usr/bin/python3 -m pip install --no-build-isolation --no-cache-dir --break-system-packages .
cd ..

echo "SUCCESS: Flash Attention installed. Ready for VILA."
