#!/bin/bash

docker build -t florence-server .

docker run -d \
  --gpus all \
  -p 8001:8001 \
  --name captioner-server-florence2 \
  florence-server


### TO TEST IT:
# Check if it's alive
#curl http://localhost:8001/health

# Send an image
#curl -X POST -F "file=@demo_images/demo_img.png" http://localhost:8001/caption
