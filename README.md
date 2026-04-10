# EmbodiedLGR: Integrating Lightweight Graph Representation and Retrieval for Semantic-Spatial Memory in Robotic Agents

[![ROS 2](https://img.shields.io/badge/ROS_2-22314E?style=flat&logo=ros&logoColor=white)](https://docs.ros.org/)
[![Docker](https://img.shields.io/badge/Docker-2496ED?style=flat&logo=docker&logoColor=white)](https://www.docker.com/)
[![Milvus](https://img.shields.io/badge/Milvus-0D1526?style=flat&logo=milvus&logoColor=white)](https://milvus.io/)
[![Gazebo](https://img.shields.io/badge/Gazebo_Harmonic-FF6600?style=flat&logo=gazebo&logoColor=white)](https://gazebosim.org/)
[![Florence-2](https://img.shields.io/badge/Florence--2-FFD21E?style=flat&logo=huggingface&logoColor=black)](https://huggingface.co/microsoft/Florence-2-large)

EmbodiedLGR is an agentic architecture enabling LLMs to reason over semantic-spatial information for agents deployed on robotic platforms.
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
To test the performance over the NaVQA dataset, clone **coda_devkit** and **remembr** inside a new `NaVQA_eval` folder on the device, and process the coda dataset following the official ReMEmbR guide. To allow visibility of the global folder, expose it correctly in the main container's `Dockerfile`.

First follow the "Launching the Containers" section, and build the packages from the main cointainer with `./buildPackages`.

Before launching the processing, replace the bash files and scripts of the original repositories from CODA and ReMEmbR with the ones in `utility/evaluation_scripts_patch`.
The **fully-automated process** can be ran by copying `runfulleval.sh` inside `remembr/remembr` and running it, selecting VLM and sequences to test. Note that the "Extract Dataset Captions and Labels" passage is still needed. Otherwise, single sequences can be tested as in the following subsections.

### Extract Dataset Captions and Labels (CODA Player)
To process the CODA dataset sequences and extract both the narrative captions and dense labels (`dlabels`) from .pkl files using Florence-2, use the `coda_player` node. 

Make sure your Florence-2 container/server is running, then execute the player for your desired sequence (e.g., Sequence 0) specifying the requested extraction interval to match the desired processing FPS:
```
cd /app/NaVQA_eval/remembr/remembr/
ros2 run waffle_agent coda_player --ros-args -p seconds_per_frame:=2.0
```

### Generate the QA Dataset
Parse the processed captions to generate the ground-truth testing questions for a specific sequence:
```
python3 scripts/question_scripts/form_question_jsons.py --caption_file captions_Florence2-large_2_secs --seq_id 0
```
### Initialize Memory Handlers
Inside the main container, launch the vector database and memory graph managers to wait for incoming data in three separate terminals:
```
ros2 run waffle_agent memory_builder_node
ros2 run waffle_agent graphmemory_manager
/usr/bin/python3 remembr_server.py
```
### Populate Memory from JSON
Inside the main container, after preprocessing captions and labels inside `remembr/remembr/data/captions` for each interested sequence, spool the memory entries inside the nodes with:
```
ros2 run waffle_agent json_memory_populator --ros-args -p json_path:="./data/captions/0/captions_Florence2-large_2_secs.json"
```
### Evaluate the agent
Inside the main container, evaluate the agent on the cosidered sequence:
```
ros2 run waffle_agent rosa_navqa_evaluator --ros-args -p sequence_id:=0 -p memory_mode:="both" -p vlm_name:="Florence2-large"
```








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
