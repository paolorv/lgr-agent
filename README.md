# CuriosityAgent: a long-term-memory agent for robotics frameworks
CuriosityAgent is a memory-enhanced reasoning pipeline for LLMs in Agentic-AI-enhanced ROS2 robotic platforms
The current project is still in testing phase.
Further details will be added once the project reaches further development steps.

## Launching the containers
### Run ROSA+ReMEmbR `rosa-ltm` container:
`./start.sh`

### Run MilvusDB
MilvusDB is required by ReMEmbR inside the rosa-ltm container to work
`cd milvusconfig`
`bash milvus_patch.sh stop   # IF NEEDED`
`bash milvus_patch.sh delete # IF NEEDED`
`bash milvus_patch.sh start`

### Run Captioner Server
The Captioner Server allows to run Florence-2 VLM to build memory from the agent
`cd captionerserver`
`./startserver.sh`

## Testing on rosa-ltm
Suggested terminal manager: `tmux`

### Gazebo simulation
`./runwafflehz.sh`
### ROSA agent (querying)
`start`  ----> Also builds the package, run before running Captioner+Memory nodes
### Captioner Node
`./runCaptionerNode.sh`
### Memory Builder Node
`./runMemoryBuilding.sh`
### To Teleoperate the robot
`./runcamerafeed.sh`
`./runteleop.sh`
The above services are all required to perform the current memory building tests.
Once the memory building steps have been completed, simply close the Memory Builder Node and the Captioner Node.

### Testing built memory
To test the built memory with queries through ROSA agent, it's required to launch beforehand the local ReMEmbR request handler as:
`python captioner_server.py`
If the server doesn't launch, run it as:
`/usr/bin/python3 captioner_server.py`


## Additional notes
### Test vila-server
VILA was tested as standalone, as the VLM originally used by ReMEmbR.
It works well with CUDA12, was untested with CUDA13.
**It's currently not required.**

To run it:
/!\ Choose Port 8001, because 8000 is used by ReMEmbR server
`git clone https://github.com/NVlabs/VILA.git`
`cd VILA`
--> COPY THE CORRECTED `Dockerfile` AND `environment_setup.sh` from directory "VILA CONFIGS" inside the "VILA" folder just cloned

`docker build -t vila-server:latest .`
`docker run --gpus all --ipc=host --ulimit memlock=-1 --ulimit stack=67108864     -v ./hub:/root/.cache/huggingface/hub     -it --rm -p 8001:8001     -e VILA_MODEL_PATH=Efficient-Large-Model/NVILA-3B     -e VILA_CONV_MODE=auto     vila-server:latest`