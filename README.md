# EmbodiedLGR: Integrating Lightweight Graph Representation and Retrieval for Semantic-Spatial Memory in Robotic Agents
EmbodiedLGR is an agentic architecture enabling LLMs to reason over semantic-spatial information for agents deployed on robotic platforms.
The current project is still in testing phase.
Further details may be added once the project reaches further development steps.

## Launching the containers
### Main Agent container (ROS2+EmbodiedLGR-Agent):
To build and launch the main container run:
```
cd curiosityagent/
./start.sh
```
Once the container is up, specify the OpenAI API Key in an .env file, or change the llm passed to the architecture.
To launch terminals inside the main container, `tmux` is strongly suggested.


### Florence-2 container
The Florence-2 container allows to run `Florence-2-large` to build memory during exploration.
To build and launch the server, run:
```
cd captionerserver/
./startserver.sh
```


### MilvusDB container
MilvusDB is required by ReMEmbR primives inside the main container to work.
To build and run the container:
```
cd milvusserver/
bash milvus_patch.sh start
```
If the container already exists, before starting it run:
```
bash milvus_patch.sh stop
bash milvus_patch.sh delete
```

## Run the agent
### Build the packages
Once inside the main agent container, build the packages as:
```
cd /app/
./buildPackages.sh
```
### Launch a simulation environment in Gazebo
To test the agent in Gazebo Harmonic over an AgileX Scout robot, run in two separate terminals:
```
cd /app/
./launchScoutSimulation.sh
./launchScoutNAV2.sh
```

### Launch memory building on graph and vectorDB
To launch the memory building for the graph memory, run in two separate terminals:
```
cd /app/
./runLabelerNode.sh
./runGraphBuilderManager.sh
```
To launch the memory building for the vector database, run in two separate terminals:
```
cd /app/
./runCaptionerNode.sh
./runRemembrMemoryBuilding.sh
```
### Test the EmbodiedLGR-agent
To test the agent, ensure the `graphmemory_manager` node is still operative, as it was launched by `./runGraphBuilderManager` and it handles access to the built graph by the agent.
To allow the agent to query the vectorDB through ReMEmbR, launch the ReMEmbR request handler in a separate terminal:
```
cd /app/
/usr/bin/python3 remembr_server.py
```
Once both memory structures are accessible, test the EmbodiedLGR-Agent by running:
```
cd /app/
start
```


## Evaluate with NaVQA 
To test the performance over the NaVQA dataset, clone and process the coda_devkit following the official ReMEmbR guide.
Before launching the processing, replace the unsafe bash files and scripts of the original repository with the ones in `utility/evaluation_scripts_patch`.



## Additional notes
### Test vila-server
VILA was tested as standalone, as the VLM originally used by ReMEmbR.
It works well with CUDA12, was untested with CUDA13.
**It's currently not required.**

To run it:
/!\ Choose Port 8001, 8000 is used by the ReMEmbR handler
```
git clone https://github.com/NVlabs/VILA.git
cd VILA/
```
--> Copy the corrected `Dockerfile` and `environment_setup.sh` from `utility/VILA_tests` to the "VILA" folder just cloned, replacing the original files.

To then test the container, run:
```
docker build -t vila-server:latest .
docker run --gpus all --ipc=host --ulimit memlock=-1 --ulimit stack=67108864     -v ./hub:/root/.cache/huggingface/hub     -it --rm -p 8001:8001     -e VILA_MODEL_PATH=Efficient-Large-Model/NVILA-3B     -e VILA_CONV_MODE=auto     vila-server:latest
```