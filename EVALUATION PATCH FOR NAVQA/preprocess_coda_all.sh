export CODA_ROOT_DIR=/mnt/1Tb-u/NaVQA_eval/coda-devkit/data
export REMEMBR_PATH=/mnt/1Tb-u/NaVQA_eval/remembr/remembr

#for i in 0;
#do
    # need to download the data
#    cd /mnt/1Tb-u/NaVQA_eval/coda-devkit
#    python scripts/extract_splits.py -d ./data -t sequence -se $i <<< "Y"
    
    # need to process the data
#    cd /mnt/1Tb-u/NaVQA_eval/remembr/remembr
#    python scripts/preprocess_coda.py -s $i

#done

export CODA_ROOT_DIR=/mnt/1Tb-u/NaVQA_eval/coda-devkit/data
export REMEMBR_PATH=/mnt/1Tb-u/NaVQA_eval/remembr/remembr

for i in 3 4 6;
do
    cd /mnt/1Tb-u/NaVQA_eval/coda-devkit
    python scripts/extract_splits.py -d ./data -t sequence -se $i <<< "Y"
    
    cd /mnt/1Tb-u/NaVQA_eval/remembr/remembr
    PYTHONPATH=/mnt/1Tb-u/NaVQA_eval/coda-devkit python scripts/preprocess_coda.py -s $i
done



