#!/bin/bash
set -e # Exit immediately if any command fails

# 1. Install Build Dependencies
# We use --break-system-packages because Ubuntu 24.04 protects system python.
# In a Docker container, this is safe to override.
/usr/bin/python3 -m pip install packaging ninja psutil setuptools wheel --break-system-packages

# 2. Clone and Setup Repo
rm -rf flash-attention # Cleanup if it exists
git clone https://github.com/Dao-AILab/flash-attention.git
cd flash-attention
git checkout v2.5.8
git submodule update --init --recursive

# 3. Set Environment Variables for RTX 5070 / CUDA 13
export MAX_JOBS=4
export FLASH_ATTENTION_FORCE_BUILD=TRUE
export CUDA_HOME=/usr/local/cuda ###CHECK IF WE NEED TO PUT cuda-12.4 HERE AS SUGGESTED BY THE TUTORIAL###

# CRITICAL FOR RTX 5070:
# FA 2.5.8 is too old to know about Blackwell (Compute Capability 10.x).
# We target Hopper (9.0) + PTX. The driver will JIT compile the PTX for your 5070.
export TORCH_CUDA_ARCH_LIST="8.0 8.6 8.9 9.0+PTX"

# 4. Build and Install
# --no-build-isolation: Uses the ninja/packaging we installed in step 1
# --no-cache-dir: Keeps the image smaller
echo "Starting compilation... this usually takes 5-10 minutes."
/usr/bin/python3 -m pip install --no-build-isolation --no-cache-dir --break-system-packages .

### If we want to just generate the wheel, remove --no-cache-dir or:
# -w /tmp/wheels : tells pip to save the .whl file in /tmp/wheels
# --no-deps      : tells pip NOT to download dependencies (torch, etc), just build this one package
#mkdir -p /tmp/wheels
#/usr/bin/python3 -m pip wheel . \
#    --no-build-isolation \
#    --no-deps \
#    --break-system-packages \
#    -w /tmp/wheels


# 5. Verify
cd ..
/usr/bin/python3 -c "import flash_attn; print(f'Success: Flash Attention {flash_attn.__version__} installed')"
