import os
import glob
import json
import pickle as pkl
import requests
import cv2
import gc
import rclpy
from rclpy.node import Node

class NumpyEncoder(json.JSONEncoder):
    def default(self, obj):
        import numpy as np
        if isinstance(obj, np.ndarray):
            return obj.tolist()
        return super(NumpyEncoder, self).default(obj)

class CodaDatasetPlayer(Node):
    def __init__(self):
        super().__init__('coda_dataset_player')
        
        self.declare_parameter('coda_data_dir', './coda_data')
        self.declare_parameter('florence_api', 'http://localhost:8001')
        self.declare_parameter('seconds_per_frame', 2.0)
        
        self.data_dir = self.get_parameter('coda_data_dir').value
        self.api_url = self.get_parameter('florence_api').value
        self.time_interval = self.get_parameter('seconds_per_frame').value

        self.get_logger().info("Offline Dataset Parser Initialized. No ROS topics will be published.")
        self.play_all_sequences()

    def play_all_sequences(self):
        if not os.path.exists(self.data_dir):
            self.get_logger().error(f"Data directory {self.data_dir} does not exist!")
            return

        seq_folders = [f for f in os.listdir(self.data_dir) if os.path.isdir(os.path.join(self.data_dir, f)) and f.isdigit()]
        seq_folders.sort(key=int)

        if not seq_folders:
            self.get_logger().error(f"No numeric sequence folders found in {self.data_dir}")
            return

        self.get_logger().info(f"Found sequences to process: {seq_folders}")

        for seq_id in seq_folders:
            #if seq_id == '0':
            #    continue
            self.get_logger().info(f"\n=========================================\nStarting extraction for Sequence {seq_id}\n=========================================")
            self.play_sequence(seq_id)

        self.get_logger().info("\n*** ALL SEQUENCES EXTRACTED SUCCESSFULLY ***")

    def play_sequence(self, seq_id):
        pkl_files = glob.glob(os.path.join(self.data_dir, str(seq_id), '*.pkl'))
        pkl_files.sort(key=lambda x: float(os.path.basename(x).replace('.pkl', '')))
        
        captions_out = []
        last_time = -1.0

        for pkl_file in pkl_files:
            timestamp = float(os.path.basename(pkl_file).replace('.pkl', ''))
            
            if last_time > 0 and (timestamp - last_time) < self.time_interval:
                continue
            last_time = timestamp

            with open(pkl_file, 'rb') as f:
                data = pkl.load(f)

            # Extract Image for API
            cv_img = data['cam0']
            _, buffer = cv2.imencode('.jpg', cv_img)
            img_bytes = buffer.tobytes()
            
            try:
                # 1. Get Caption
                resp_cap = requests.post(f"{self.api_url}/caption", files={'file': ('f.jpg', img_bytes, 'image/jpeg')})
                caption_text = resp_cap.json().get('result', '')
                
                # 2. Get Object Labels (<OD>)
                resp_lab = requests.post(f"{self.api_url}/labels", files={'file': ('f.jpg', img_bytes, 'image/jpeg')})
                labels_dict = resp_lab.json().get('result', {})
                labels_list = labels_dict.get('labels', []) if isinstance(labels_dict, dict) else labels_dict

                # 3. Get Dense Labels (<DENSE_REGION_CAPTION>)
                resp_dlab = requests.post(f"{self.api_url}/dlabels", files={'file': ('f.jpg', img_bytes, 'image/jpeg')})
                dlabels_dict = resp_dlab.json().get('result', {})
                dlabels_list = dlabels_dict.get('labels', []) if isinstance(dlabels_dict, dict) else dlabels_dict

                # 4. Save directly to JSON struct
                filename = f"{timestamp}.pkl"
                captions_out.append({
                    "id": filename,
                    "file_start": filename,
                    "file_end": filename,
                    "time": timestamp,
                    "position": data['position'].tolist(),
                    "caption": caption_text,
                    "labels": labels_list,
                    "dlabels": dlabels_list
                })    

                self.get_logger().info(f"Seq {seq_id} | t={timestamp:.1f} | OD: {len(labels_list)} | Dense: {len(dlabels_list)}")

            except Exception as e:
                self.get_logger().error(f"Florence API Error: {e}")

            # --- CRITICAL MEMORY CLEANUP ---
            del data
            del cv_img
            del buffer
            del img_bytes
            gc.collect()

        # Save to disk
        out_dir = f"./data/captions/{seq_id}"
        os.makedirs(out_dir, exist_ok=True)
        json_filename = f"{out_dir}/captions_Florence2-base-ft_{int(self.time_interval)}_secs.json"
        
        with open(json_filename, 'w') as f:
            json.dump(captions_out, f, cls=NumpyEncoder, indent=4)
        
        self.get_logger().info(f"Extraction Complete for Sequence {seq_id}. JSON saved.")

def main(args=None):
    rclpy.init(args=args)
    node = CodaDatasetPlayer()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
