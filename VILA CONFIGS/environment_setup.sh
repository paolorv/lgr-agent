#!/usr/bin/env bash
set -e

#CONDA_ENV=${1:-""}
#if [ -n "$CONDA_ENV" ]; then
#    # This is required to activate conda environment
#    eval "$(conda shell.bash hook)"

#    conda create -n $CONDA_ENV python=3.10.14 -y
#    conda activate $CONDA_ENV
    # This is optional if you prefer to use built-in nvcc
#    conda install -c nvidia cuda-toolkit -y
#else
#    echo "Skipping conda environment creation. Make sure you have the correct environment activated."
#fi

# This is required to enable PEP 660 support
pip install --upgrade pip setuptools

# Install FlashAttention2
pip install https://github.com/Dao-AILab/flash-attention/releases/download/v2.5.8/flash_attn-2.5.8+cu122torch2.3cxx11abiFALSE-cp310-cp310-linux_x86_64.whl

# We uninstall whatever the script installed and force the stable version
#RUN pip uninstall -y opencv-python opencv-python-headless \
#    && pip install opencv-python-headless==4.9.0.80

pip uninstall -y opencv-python opencv-python-headless opencv-contrib-python || true



# Install VILA
pip install -e ".[train,eval]"

# FIX: Install the missing NVILA dependencies
pip install --no-cache-dir ps3-torch
# FIX II: Downgrade OpenCV to fix 'DictValue' error
# 2. Install the specific version known to work with VILA/VLLM
pip install opencv-python-headless==4.7.0.72

# Quantization requires the newest triton version, and introduce dependency issue
#pip install triton==3.1.0
pip install triton==3.3.1

# numpy introduce a lot dependencies issues, separate from pyproject.yaml
# pip install numpy==1.26.4

# Replace transformers and deepspeed files
site_pkg_path=$(python -c 'import site; print(site.getsitepackages()[0])')
cp -rv ./llava/train/deepspeed_replace/* $site_pkg_path/deepspeed/

#python -m pip install git+https://github.com/huggingface/transformers@v4.37.2
pip install transformers==4.46.0 tokenizers==0.20.3
site_pkg_path=$(python -c 'import site; print(site.getsitepackages()[0])')
#cp -rv ./llava/train/transformers_replace/* $site_pkg_path/transformers/
cp -rv ./llava/train/deepspeed_replace/* $site_pkg_path/deepspeed/

# Downgrade protobuf to 3.20 for backward compatibility
pip install protobuf==3.20.*
