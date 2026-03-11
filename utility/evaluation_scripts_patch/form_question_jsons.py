import json
import pandas as pd
import os
import time
import datetime
from time import strftime, localtime
import numpy as np
import argparse

DATA_CSV = "./data/navqa/data.csv"
DATA_PATH = "./data"

parser = argparse.ArgumentParser(
                    prog='Long Horizontal Robot QA',
                    description='Runs various LLMs on the QA dataset',)

# data-specific args
parser.add_argument("--caption_file", type=str, default="captions_Llama-3-VILA1.5-8b_3_secs")
# ---> ADDED seq_id ARGUMENT <---
parser.add_argument("--seq_id", type=int, required=True, help="The specific sequence ID to process")
args = parser.parse_args()

CAPTIONS_PATH = './data/captions/{seq_id}' + f'/{args.caption_file}.json'


def format_docs(docs):
    out_string = ""
    for doc in docs:
        t = localtime(doc['time'])
        t = strftime('%Y-%m-%d %H:%M:%S', t)

        s = f"At time={t}, the robot was at an average position of {np.array(doc['position']).round(3).tolist()}."
        s += f"The robot saw the following: {doc['caption']}\n\n"
        out_string += s
    return out_string


def parse_answer(answer, context, qa_pair):

    q_type = answer['Type \n(binary, position, time, text)']
    text_answer = answer['Text answer']
    parsable_answer = answer['Parsable answer']
    out_dict = None

    if q_type == 'binary':
        out_dict = {'text': [parsable_answer, parsable_answer]}
    elif q_type == 'text': 
        out_dict = {'text': [text_answer]}
    elif q_type == 'position':
        if len(context) == 1:
            out_dict = {'position': context[0]['position']}
    elif q_type == 'time':
        if len(context) == 1:
            answer_time = context[0]['time'] 
            current_time = qa_pair['end_time']
            minutes_ago = np.round((current_time - answer_time)/60, 2)
            out_dict = {
                'text': [str(minutes_ago) + ' minutes ago'],
                'time': minutes_ago
            }
    elif q_type == 'duration':
        out_dict = {
            'text': [str(parsable_answer.strip()) + ' minutes'],
            'duration': float(parsable_answer.strip())
        }
    
    if out_dict is None:
        print("NOT EVERYTHING WAS PARSED CORRECTLY POSSIBLY!")
        print("Filling in un-parsable out_dict")
        out_dict = {'text': [text_answer], q_type: parsable_answer}
        
    return out_dict


# Load the CSV data once
data = pd.read_csv(DATA_CSV)

# ---> REMOVED GLOB LOOP. PROCESS ONLY THE REQUESTED SEQ_ID <---
seq_id = args.seq_id
print("On SeqID", seq_id)
all_questions = []

unfilled_qa_path = os.path.join('./data', 'navqa', str(seq_id), 'qa_unfilled.json')

if not os.path.exists(unfilled_qa_path):
    print(f"ERROR: No qa_unfilled.json found for SeqID {seq_id} at {unfilled_qa_path}")
    exit(1)

with open(unfilled_qa_path, 'r') as f:
    unfilled_qa = json.load(f)['data']

try:
    with open(CAPTIONS_PATH.format(seq_id = seq_id)) as f:
        captions = json.load(f)
except:
    print(f"ERROR. Questions for {seq_id} exists, however, captions do not exist. Will skip SeqID {seq_id}")
    exit(1)

# get the specific subset
subset_df = data[(data["Seq ID"] == seq_id) & (data["Question"] != "") & (data['Question'].notna())]

if len(subset_df) > 0:
    for qa_pair in unfilled_qa: 
        id = qa_pair['id']
        answers = subset_df[subset_df['UUID'] == id]

        caption_start_ids = [item['id'] for item in captions]
        caption_start_ids.sort(key=lambda x: float(x.split('/')[-1][:-4])) 
        caption_times = np.array([float(file.split('/')[-1][:-4]) for file in caption_start_ids])

        for _, answer in answers.iterrows():
            filled_qa = qa_pair.copy()
            text_answer_timestamp = answer['Timestamp \nwith answer']
            question = answer['Question']
            q_type = answer['Type \n(binary, position, time, text)']
            q_category = answer['Question\nCategory']

            t = localtime(filled_qa['start_time'])
            mdy_date = strftime('%m/%d/%Y', t)
            template = "%m/%d/%Y %H:%M:%S"

            context_starts = []
            context_ends = []
            context_captions = []

            for hms_time in text_answer_timestamp.split(','):
                hms_time = hms_time.strip()
                full_time = mdy_date + ' ' + hms_time
                timestamp = time.mktime(datetime.datetime.strptime(full_time,template).timetuple())

                diff = caption_times - timestamp
                caption_idx = np.argmax(diff > 0) - 1
                context_captions.append(captions[caption_idx])

                context_starts.append(captions[caption_idx]['file_start'])
                context_ends.append(captions[caption_idx]['file_end'])

            context = format_docs(context_captions)
            context_starts.sort(key=lambda x: float(x[:-4]))
            context_starts = context_starts[0]
            context_ends.sort(key=lambda x: float(x[:-4]))
            context_ends = context_ends[-1]

            current_time = localtime(filled_qa['end_time'])
            current_time = strftime('%Y-%m-%d %H:%M:%S', current_time)   

            start_time = localtime(filled_qa['start_time'])
            start_time = strftime('%Y-%m-%d %H:%M:%S', start_time)   

            diff = caption_times - filled_qa['end_time']
            caption_idx = np.argmax(diff > 0) - 1
            current_position = np.round(np.array(captions[caption_idx]['position']), 2).tolist()

            question = f"You started moving at {start_time}. The current time is {current_time} and you are located at {current_position}. \n {question}"

            filled_qa['question'] = question
            filled_qa['type'] = q_type
            filled_qa['context'] = context
            filled_qa['file_info']['context_start_filename'] = context_starts
            filled_qa['file_info']['context_end_filename'] = context_ends

            parsed_answer = parse_answer(answer, context_captions, filled_qa)
            filled_qa['answers'] = parsed_answer
            all_questions.append(filled_qa)

# save all_questions into json
out_json = {
    "version": 0.1,
    "data": all_questions
}

print(f"Saving data for sequence {seq_id} in ./data/questions/{seq_id}/human_qa.json")
os.makedirs(f'./data/questions/{seq_id}', exist_ok=True)

with open(f'./data/questions/{seq_id}/human_qa.json', 'w') as f:
    json.dump(out_json, f, indent=4)