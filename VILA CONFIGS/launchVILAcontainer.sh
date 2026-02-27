docker run --runtime nvidia --gpus all \
    --ipc=host \
    -p 8001:8001 \
    --name vila-server \
    -v ~/.cache/huggingface:/root/.cache/huggingface \
    vllm/vllm-openai:latest \
    --model Efficient-Large-Model/VILA1.5-3b \
    --trust-remote-code \
    --max-model-len 4096 \
    --dtype half