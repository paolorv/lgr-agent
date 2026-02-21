#!/bin/bash

docker build -t florence-server .

docker run -d \
  --runtime nvidia \
  -p 8001:8001 \
  --name captioner-server-florence2 \
  florence-server