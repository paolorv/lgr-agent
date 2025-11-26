# 1. Remove any failed partial installs
pip uninstall -y flash-attn

# 2. Clone the repository (Do NOT use pip install flash-attn)
# We use the main branch because 5070 support is bleeding edge.
rm -rf flash-attention
git clone https://github.com/Dao-AILab/flash-attention.git
cd flash-attention
git submodule update --init --recursive

########## ADD GIT CHECKOUT IF YOU WANT A SPECIFIC COMMIT ########## LIKE 2.5.8


# 3. SET BUILD LIMITS (Crucial to fix "Killed")
# Limiting to 1 job prevents your RAM from filling up. 
# It will be slower (10-20 mins), but it will not crash.
export MAX_JOBS=1 ##Set according to processor

# 4. SET ARCHITECTURE
# We force Hopper (9.0) + PTX (JIT). 
# This is safer than letting the script guess "sm_120" and failing.
export TORCH_CUDA_ARCH_LIST="9.0+PTX"

# 5. COMPILE
echo "Starting compilation... this will take time. Be patient."
#pip install --no-build-isolation --no-cache-dir .
pip install --no-build-isolation .