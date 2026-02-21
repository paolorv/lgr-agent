#!/bin/bash

docker build -t florence-server .

# Replaced --gpus all with --runtime nvidia
docker run -d \
  --runtime nvidia \
  -p 8001:8001 \
  --name captioner-server-florence2 \
  florence-server