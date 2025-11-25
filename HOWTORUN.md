# Start 3 containers: rosa-ltm, milvusdb, vila-server
### To run rosa-ltm:
cd GitRepositoris/curiosityagent
./start.sh
### To run milvusdb
cd GitRepositoris/curiosityagent/milvusconfig
bash milvus_patch.sh stop   # IF NEEDED
bash milvus_patch.sh delete # IF NEEDED
bash milvus_patch.sh start

### To run vila-server
/!\ Choose Port 8001, because 8000 is used by ReMEmbR server
**** ADD WORKING METHOD FOR 5070 ****
Otherwise:
git clone https://github.com/NVlabs/VILA.git
cd VILA
docker build -t vila-server:latest .
docker run --gpus all --ipc=host --ulimit memlock=-1 --ulimit stack=67108864     -v ./hub:/root/.cache/huggingface/hub     -it --rm -p 8000:8000     -e VILA_MODEL_PATH=Efficient-Large-Model/NVILA-15B     -e VILA_CONV_MODE=auto     vila-server:latest


## Once inside rosa-ltm
tmux
### Terminal 1
./runwafflehz.sh
### Terminal 2
start
### Terminal 3
****ADD RUN CAPTIONER NODE FROM ros2 run waffle_agent****
### Terminal 4
RUN TELEOP+LIVE CAMERA FEED
