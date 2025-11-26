### RUN VILA1.5 WITH CUDA 13.0, PYTHON 3.10 (CONDA), TORCH 2.9.1 FOR CUDA 13.0, SELF-COMPILED FLASH-ATTN 2.8.6

### Activate environment
source /opt/conda/bin/activate
conda activate vila

### Install CUDA
---> See my tutorial on Notion (or, if we need CUDA 12.4: https://gist.github.com/helena-intel/2afc89e8b9eb08105d080a8cdc6127ac?utm_source=chatgpt.com)
Otherwise,
sudo wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2404/x86_64/cuda-keyring_1.1-1_all.deb && \
sudo dpkg -i cuda-keyring_1.1-1_all.deb && \
sudo apt-get update && \
sudo apt-get -y install cuda-toolkit-13-0

If the `nvcc --version` command doesn't work, install:
sudo apt-get -y install nvidia-cuda-toolkit

### Clone VILA repository
git clone https://github.com/NVlabs/VILA.git
cd VILA

### FIX IMPORT in VILA/llava/model/qfunction.py adding on top of file:
import sys, os
sys.path.append(os.path.dirname(os.path.abspath(__file__)))


### INSTALL DEPENDENCIES WITH CONFIG FILE (In a conda environment enabled)
./environment_setup.sh vila

### INSTALL NEW TRITON 3.3.1 (probably gets overwritten)
pip install triton==3.3.1

### INSTALL PS3
pip install ps3-torch

### INSTALL TORCH ENABLED FOR CUDA 13.0
pip3 install torch torchvision --index-url https://download.pytorch.org/whl/cu130 


### COMPILE AND INSTALL FLASH_ATTENTION FOR CUDA 13.0, USE LATEST VERSION!
# 1. Remove any failed partial installs
pip uninstall -y flash-attn

# 2. Clone the repository (Do NOT use pip install flash-attn)
# We use the main branch because 5070 support is bleeding edge.
rm -rf flash-attention
git clone https://github.com/Dao-AILab/flash-attention.git
cd flash-attention
git submodule update --init --recursive

# 3. SET BUILD LIMITS (Crucial to fix "Killed")
# Limiting to 1 job prevents your RAM from filling up. 
# It will be slower (10-20 mins), but it will not crash.
export MAX_JOBS=1

# 4. SET ARCHITECTURE
# We force Hopper (9.0) + PTX (JIT). 
# This is safer than letting the script guess "sm_120" and failing.
export TORCH_CUDA_ARCH_LIST="9.0+PTX"

# 5. COMPILE
echo "Starting compilation... this will take time. Be patient."
#pip install --no-build-isolation --no-cache-dir .   # IF WE DON'T WANT TO CACHE THE WHEEL .whl
pip install --no-build-isolation .  # HERE THE -NO-BUILD-ISOLATION IS REQURED BECAUSE FLASH ATTN NEEDS TO EXPLOIT TORCH VERSION

### IF NEEDED, OWN THE HUGGINGFACE PERMISSION CACHE:
sudo chown -R even:even /home/even/.cache/huggingface
chmod ...


## RUN     THE       MODEL
vila-infer     --model-path Efficient-Large-Model/VILA1.5-3b     --conv-mode vicuna_v1     --text "Please describe the video"     --media car.jpg 




############################### FURTHER DETAILS ON ISSUES (IF EVER NEEDED) ################################################
FROM: https://github.com/NVlabs/VILA/issues/258

Hey. After some trial and error I was able to run the docker.

For that particular error, you should add the line

pip install ps3-torch

As well, I found you should upgrade the triton dependency

pip install triton==3.3.1

Another error i found is the following

    ValueError: Cannot use chat template functions because tokenizer.chat_template is not set and no template argument was passed! For information about writing templates and setting the tokenizer.chat_template attribute, please see the documentation at https://huggingface.co/docs/transformers/main/en/chat_templating

In order to solve this, you should add the following line to the tokenizer_config.json of the model you want to use, in my case it was Efficient-Large-Model/VILA1.5-3b

` "chat_template": "{% for message in messages %}\n{% if message['role'] == 'user' %}\n{{ '<|user|>\n' + message['content'] + eos_token }}\n{% elif message['role'] == 'system' %}\n{{ '<|system|>\n' + message['content'] + eos_token }}\n{% elif message['role'] == 'assistant' %}\n{{ '<|assistant|>\n'  + message['content'] + eos_token }}\n{% endif %}\n{% if loop.last and add_generation_prompt %}\n{{ '<|assistant|>' }}\n{% endif %}\n{% endfor %}",

In my setting, this file is stored in the following path

    ~/.cache/huggingface/hub/models--Efficient-Large-Model--VILA1.5-3b/snapshots/llm/tokenizer_config.json

Last error I found was related to a failure importing FloatPointQuantizeTorch.
For this, simply add the following line on top of the file with the import error.

sys.path.append(os.path.dirname(os.path.abspath(__file__)))




################################################################# DETAILS ############################################################################
(vila) even@even-PC:~/Tests$ pip show torch
Name: torch
Version: 2.9.1+cu130
Summary: Tensors and Dynamic neural networks in Python with strong GPU acceleration
Home-page: https://pytorch.org
Author: 
Author-email: PyTorch Team <packages@pytorch.org>
License: BSD-3-Clause
Location: /home/even/.conda/envs/vila/lib/python3.10/site-packages
Requires: filelock, fsspec, jinja2, networkx, nvidia-cublas, nvidia-cuda-cupti, nvidia-cuda-nvrtc, nvidia-cuda-runtime, nvidia-cudnn-cu13, nvidia-cufft, nvidia-cufile, nvidia-curand, nvidia-cusolver, nvidia-cusparse, nvidia-cusparselt-cu13, nvidia-nccl-cu13, nvidia-nvjitlink, nvidia-nvshmem-cu13, nvidia-nvtx, sympy, triton, typing-extensions
Required-by: accelerate, bitsandbytes, deepspeed, flash_attn, peft, ps3-torch, timm, torchvision, vila, xgrammar

(vila) even@even-PC:~/Tests$ pip show transformers
Name: transformers
Version: 4.46.0
Summary: State-of-the-art Machine Learning for JAX, PyTorch and TensorFlow
Home-page: https://github.com/huggingface/transformers
Author: The Hugging Face team (past and future) with the help of all our contributors (https://github.com/huggingface/transformers/graphs/contributors)
Author-email: transformers@huggingface.co
License: Apache 2.0 License
Location: /home/even/.conda/envs/vila/lib/python3.10/site-packages
Requires: filelock, huggingface-hub, numpy, packaging, pyyaml, regex, requests, safetensors, tokenizers, tqdm
Required-by: peft, ps3-torch, vila, xgrammar

(vila) even@even-PC:~/Tests$ pip show triton
Name: triton
Version: 3.5.1
Summary: A language and compiler for custom Deep Learning operations
Home-page: https://github.com/triton-lang/triton/
Author: Philippe Tillet
Author-email: phil@openai.com
License: 
Location: /home/even/.conda/envs/vila/lib/python3.10/site-packages
Requires: 
Required-by: torch, xgrammar

(vila) even@even-PC:~/Tests$ nvcc --version
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2025 NVIDIA Corporation
Built on Wed_Aug_20_01:58:59_PM_PDT_2025
Cuda compilation tools, release 13.0, V13.0.88
Build cuda_13.0.r13.0/compiler.36424714_0

(vila) even@even-PC:~/Tests$ pip show flash_attn
Name: flash_attn
Version: 2.8.3
Summary: Flash Attention: Fast and Memory-Efficient Exact Attention
Home-page: https://github.com/Dao-AILab/flash-attention
Author: Tri Dao
Author-email: tri@tridao.me
License: 
Location: /home/even/.conda/envs/vila/lib/python3.10/site-packages
Requires: einops, torch
Required-by: 



################################### GENERATED PIP REQUIREMENTS AT THE TIME IT STARTED ##########################################
accelerate==0.34.2
aiofiles==25.1.0
aiohappyeyeballs==2.6.1
aiohttp==3.13.2
aiosignal==1.4.0
altair==6.0.0
annotated-doc==0.0.4
antlr4-python3-runtime==4.9.3
anyio==4.11.0
async-timeout==5.0.1
attrs==25.4.0
av==16.0.1
bitsandbytes==0.43.2
braceexpand==0.1.7
certifi==2025.11.12
cfgv==3.5.0
charset-normalizer==3.4.4
click==8.3.1
contourpy==1.3.2
cuda-bindings==12.9.4
cuda-pathfinder==1.2.2
cycler==0.12.1
datasets==2.16.1
decord==0.6.0
deepspeed==0.9.5
dill==0.3.7
distlib==0.4.0
distro==1.9.0
docstring_parser==0.17.0
einops==0.6.1
einops-exts==0.0.4
et_xmlfile==2.0.0
exceptiongroup==1.3.1
fastapi==0.122.0
ffmpy==1.0.0
filelock==3.20.0
fire==0.7.1
flash_attn @ file:///home/even/Tests/VILA/flash-attention/flash-attention
fonttools==4.60.1
frozenlist==1.8.0
fsspec==2023.10.0
ftfy==6.3.1
fvcore==0.1.5.post20221221
gitdb==4.0.12
GitPython==3.1.45
gradio==3.35.2
gradio_client==0.2.9
h11==0.16.0
hf-xet==1.2.0
hjson==3.1.0
httpcore==1.0.9
httpx==0.28.1
huggingface-hub==0.36.0
hydra-core==1.3.2
identify==2.6.15
idna==3.11
iniconfig==2.3.0
iopath==0.1.10
Jinja2==3.1.6
joblib==1.5.2
jsonschema==4.25.1
jsonschema-specifications==2025.9.1
kiwisolver==1.4.9
latex2mathml==3.78.1
Levenshtein==0.27.3
linkify-it-py==2.0.3
loguru==0.7.3
markdown-it-py==2.2.0
markdown2==2.5.4
MarkupSafe==3.0.3
matplotlib==3.10.7
mdit-py-plugins==0.3.3
mdurl==0.1.2
mpmath==1.3.0
multidict==6.7.0
multiprocess==0.70.15
narwhals==2.12.0
networkx==3.4.2
ninja==1.13.0
nltk==3.3
nodeenv==1.9.1
numpy==1.26.4
nvidia-cublas==13.0.0.19
nvidia-cublas-cu12==12.6.4.1
nvidia-cuda-cupti==13.0.48
nvidia-cuda-cupti-cu12==12.6.80
nvidia-cuda-nvrtc==13.0.48
nvidia-cuda-nvrtc-cu12==12.6.77
nvidia-cuda-runtime==13.0.48
nvidia-cuda-runtime-cu12==12.6.77
nvidia-cudnn-cu12==9.10.2.21
nvidia-cudnn-cu13==9.13.0.50
nvidia-cufft==12.0.0.15
nvidia-cufft-cu12==11.3.0.4
nvidia-cufile==1.15.0.42
nvidia-cufile-cu12==1.11.1.6
nvidia-curand==10.4.0.35
nvidia-curand-cu12==10.3.7.77
nvidia-cusolver==12.0.3.29
nvidia-cusolver-cu12==11.7.1.2
nvidia-cusparse==12.6.2.49
nvidia-cusparse-cu12==12.5.4.2
nvidia-cusparselt-cu12==0.7.1
nvidia-cusparselt-cu13==0.8.0
nvidia-nccl-cu12==2.27.5
nvidia-nccl-cu13==2.27.7
nvidia-nvjitlink==13.0.39
nvidia-nvjitlink-cu12==12.6.85
nvidia-nvshmem-cu12==3.4.5
nvidia-nvshmem-cu13==3.3.24
nvidia-nvtx==13.0.39
nvidia-nvtx-cu12==12.6.77
omegaconf==2.3.0
openai==1.8.0
opencv-python-headless==4.8.0.76
openpyxl==3.1.2
orjson==3.11.4
packaging==25.0
pandas==2.3.3
parameterized==0.9.0
peft==0.18.0
pillow==12.0.0
platformdirs==4.5.0
pluggy==1.6.0
portalocker==3.2.0
pre_commit==4.5.0
propcache==0.4.1
protobuf==3.20.3
ps3-torch==0.1.3
psutil==7.1.3
py-cpuinfo==9.0.0
pyarrow==22.0.0
pyarrow-hotfix==0.7
pydantic==1.10.24
pydub==0.25.1
Pygments==2.19.2
pyparsing==3.2.5
pytest==9.0.1
python-dateutil==2.9.0.post0
python-multipart==0.0.20
pytorch-triton==3.5.1+gitbfeb0668
pytorchvideo==0.1.5
pytz==2025.2
pywsd==1.2.4
PyYAML==6.0.3
RapidFuzz==3.14.3
referencing==0.37.0
regex==2025.11.3
requests==2.32.5
rich==14.2.0
ring-flash-attn==0.1.1
rpds-py==0.29.0
s2wrapper @ git+https://github.com/bfshi/scaling_on_scales@9c008a37540e761f53574b488979db6e49a64312
safetensors==0.7.0
scikit-learn==1.2.2
scipy==1.15.3
seaborn==0.13.2
semantic-version==2.10.0
sentencepiece==0.1.99
sentry-sdk==2.46.0
shortuuid==1.0.13
shtab==1.8.0
six==1.17.0
smmap==5.0.2
sniffio==1.3.1
starlette==0.50.0
svgwrite==1.4.3
sympy==1.14.0
tabulate==0.9.0
termcolor==3.2.0
threadpoolctl==3.6.0
tiktoken==0.12.0
timm==1.0.22
tokenizers==0.20.3
tomli==2.3.0
torch==2.9.1+cu130
torchvision==0.24.1+cu130
tqdm==4.67.1
transformers==4.46.0
triton==3.5.1
typeguard==4.4.4
typing_extensions==4.15.0
tyro==0.9.35
tzdata==2025.2
uc-micro-py==1.0.3
urllib3==2.5.0
uvicorn==0.38.0
-e git+https://github.com/NVlabs/VILA.git@9315b7f1cdbed30abff136635b07cc24cba3fc67#egg=vila
virtualenv==20.35.4
wandb==0.23.0
wavedrom==2.0.3.post3
wcwidth==0.2.14
webdataset==0.2.86
websockets==15.0.1
wn==0.14.0
word2number==1.1
xgrammar==0.1.27
xxhash==3.6.0
yacs==0.1.8
yarl==1.22.0