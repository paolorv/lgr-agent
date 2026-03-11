#!/bin/bash

source /app/install/setup.bash

# Define sequences, VLMs, and testing modes
#SEQUENCES=(0 3 4 6 16 21)
SEQUENCES=(16)
#VLMS=("Florence2-base" "Florence2-base-ft" "Florence2-large" "Florence2-large-ft")
VLMS=("Florence2-large" "Florence2-base")
MODES=("graph" "remembr" "both")
#MODES=("both")


# Catch CTRL+C to safely kill background ROS nodes and exit
trap 'echo -e "\n\n[ABORTED] CTRL+C detected! Killing background nodes and exiting..."; kill -9 $MEM_PID $GRAPH_PID 2>/dev/null; exit 1' INT

echo "======================================================"
echo "STARTING FULL NAVQA AUTOMATED EVALUATION SUITE"
echo "======================================================"

for SEQ in "${SEQUENCES[@]}"; do
    for VLM in "${VLMS[@]}"; do
        
        # Format matches your output files: captions_Florence2-large_2_secs.json
        CAPTION_FILE="captions_${VLM}_2_secs"
        JSON_PATH="/app/NaVQA_eval/remembr/remembr/data/captions/${SEQ}/${CAPTION_FILE}.json"

        if [ ! -f "$JSON_PATH" ]; then
            echo "Skipping ${VLM} for Seq ${SEQ} (JSON not found: ${JSON_PATH})"
            continue
        fi

        echo "------------------------------------------------------"
        echo "[1/4]######################################### Generating human_qa.json for Seq: ${SEQ} | VLM: ${VLM}"
        python3 scripts/question_scripts/form_question_jsons.py --caption_file ${CAPTION_FILE} --seq_id ${SEQ}
        
        # [2/4] START MEMORY NODES
        echo -e "\n>>>################################## Starting Memory Backend for [Seq: ${SEQ}] [VLM: ${VLM}] <<<"
        
        ros2 run waffle_agent memory_builder_node &
        MEM_PID=$!
        echo "Waiting 120 seconds for memory databases to settle..."
        sleep 30
        ros2 run waffle_agent graphmemory_manager &
        GRAPH_PID=$!
        
        sleep 10 # Give ROS time to initialize nodes

        # [3/4] SPOOL MEMORY (Foreground blocking process)
        echo "###########################Spooling ${JSON_PATH} into memory...##########################################"
        ros2 run waffle_agent json_memory_populator --ros-args -p json_path:="${JSON_PATH}"
        
        # Give the Graph/Milvus nodes 5 seconds to process the very last ROS messages from the spooler
        echo "Waiting 10 seconds for memory entries to settle..."
        sleep 10


        # # ---> [NEW] START REMEMBR SERVER <---
        # echo "###########################Starting ReMEmbR Server...##########################################"
        # /usr/bin/python3 /app/remembr_server.py > /app/logs/remembr_server.log 2>&1 &
        # REMEMBR_PID=$!

        # echo "Waiting 20 seconds for memory initialization to settle..."
        # sleep 20

        # [4/4] RUN EVALUATOR (3 times consecutively)
        for MODE in "${MODES[@]}"; do
            echo -e "\n################################# Evaluating [Mode: ${MODE}] ###########################################"
            # Foreground blocking process - will wait until evaluator fully exits
            ros2 run waffle_agent evaluator_node --ros-args -p sequence_id:=${SEQ} -p memory_mode:="${MODE}" -p vlm_name:="${VLM}"
            echo -e "\n################################# FINISHED [Mode: ${MODE}] ###########################################"
	        sleep 10
        done

        # CLEANUP: Kill nodes to flush RAM for the next VLM/Sequence
        echo "/\/\/\/\//\/\/\/\//\/\/\/\//\/\/\/\/Flushing RAM for next configuration.../\/\/\/\//\/\/\/\//\/\/\/\//\/\/\/\//\/\/\/\/"
        # Kill all three background processes
        kill -9 $MEM_PID $GRAPH_PID #$REMEMBR_PID
        # Wait suppresses the "Killed" terminal output messages
        wait $MEM_PID 2>/dev/null
        wait $GRAPH_PID 2>/dev/null
        #wait $REMEMBR_PID 2>/dev/null
	sleep 5
    done
done

echo "======================================================"
echo "EVALUATION COMPLETE! Check ./out/master_evaluation_results.csv"
echo "======================================================"
