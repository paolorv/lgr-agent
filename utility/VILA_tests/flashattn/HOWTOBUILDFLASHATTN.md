### How to build FlashAttn 2.5.8 on Noble+Python3.12

### Install CUDA 12.4 on Ubuntu 24.04 (actyually pulling the version from 22.04)
From: https://gist.github.com/helena-intel/2afc89e8b9eb08105d080a8cdc6127ac?utm_source=chatgpt.com

sudo nano /etc/apt/sources.list.d/ubuntu.sources
HERE, ADD THIS:
Types: deb
URIs: http://old-releases.ubuntu.com/ubuntu/
Suites: lunar
Components: universe
Signed-By: /usr/share/keyrings/ubuntu-archive-keyring.gpg

THEN INSTALL CUDA:
curl -O https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-ubuntu2204.pin
sudo mv cuda-ubuntu2204.pin /etc/apt/preferences.d/cuda-repository-pin-600
curl -O https://developer.download.nvidia.com/compute/cuda/12.4.0/local_installers/cuda-repo-ubuntu2204-12-4-local_12.4.0-550.54.14-1_amd64.deb
sudo dpkg -i cuda-repo-ubuntu2204-12-4-local_12.4.0-550.54.14-1_amd64.deb
sudo cp /var/cuda-repo-ubuntu2204-12-4-local/cuda-*-keyring.gpg /usr/share/keyrings/
sudo apt-get update
sudo apt-get -y install cuda-toolkit-12-4

export CUDA_HOME=/usr/local/cuda-12.4/ #--->IF WE NEED THIS VAR
sudo apt install nvidia-cuda-toolkit #---->IF WE NEED TO COMPILE IN CUDA, SO "nvcc" is required(yes)

### Install Torch 2.3.0
/usr/bin/python3 -m pip install torch="2.3.0" --break-system-packages

### Run script
./installflashattn.sh

### If it worked, keep the compiled file and simply install it as:
/usr/bin/python3 -m pip install <compiledfilename>.whl


--> Skip analouge file and run the rest of the VILA config script!