import os
import glob
import json
import pickle as pkl
import time
import requests
import cv2
import gc  # Added for memory management across multiple sequences
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from nav_msgs.msg import Odometry

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
        self.declare_parameter('seconds_per_frame', 2.0) # Process 2 frames per second of sequence
        
        self.data_dir = self.get_parameter('coda_data_dir').value
        self.api_url = self.get_parameter('florence_api').value
        self.time_interval = self.get_parameter('seconds_per_frame').value

        # Publishers matching your memory nodes
        self.pub_odom1 = self.create_publisher(Odometry, '/odom', 10)       
        self.pub_odom2 = self.create_publisher(Odometry, '/odometry', 10)   
        self.pub_caption = self.create_publisher(String, '/captions', 10)
        self.pub_labels = self.create_publisher(String, '/labels', 10)

        # Start the automated sequence loop
        self.play_all_sequences()

    def play_all_sequences(self):
        """Scans the data directory and processes all sequence folders found."""
        if not os.path.exists(self.data_dir):
            self.get_logger().error(f"Data directory {self.data_dir} does not exist!")
            return

        # Find all folders in coda_data that are numbers (e.g., '0', '3', '16')
        seq_folders = [f for f in os.listdir(self.data_dir) if os.path.isdir(os.path.join(self.data_dir, f)) and f.isdigit()]
        
        # Sort them numerically so it processes sequentially
        seq_folders.sort(key=int)

        if not seq_folders:
            self.get_logger().error(f"No numeric sequence folders found in {self.data_dir}")
            return

        self.get_logger().info(f"Found sequences to process: {seq_folders}")

        for seq_id in seq_folders:
            self.get_logger().info(f"\n=========================================\nStarting playback for Sequence {seq_id}\n=========================================")
            self.play_sequence(seq_id)

        self.get_logger().info("\n*** ALL SEQUENCES PROCESSED SUCCESSFULLY ***")

    def play_sequence(self, seq_id):
        """Processes a single sequence and saves its specific JSON file."""
        pkl_files = glob.glob(os.path.join(self.data_dir, str(seq_id), '*.pkl'))
        pkl_files.sort(key=lambda x: float(os.path.basename(x).replace('.pkl', '')))
        
        captions_out = []
        last_time = -1.0

        for pkl_file in pkl_files:
            timestamp = float(os.path.basename(pkl_file).replace('.pkl', ''))
            
            # Subsample frames
            if last_time > 0 and (timestamp - last_time) < self.time_interval:
                continue
            last_time = timestamp

            with open(pkl_file, 'rb') as f:
                data = pkl.load(f)

            # 1. Publish Odometry first so memory nodes have the pose ready
            odom_msg = Odometry()
            odom_msg.header.stamp = self.get_clock().now().to_msg()
            odom_msg.header.frame_id = "map"
            odom_msg.pose.pose.position.x = float(data['position'][0])
            odom_msg.pose.pose.position.y = float(data['position'][1])
            odom_msg.pose.pose.position.z = float(data['position'][2])
            
            self.pub_odom1.publish(odom_msg)
            self.pub_odom2.publish(odom_msg)
            time.sleep(0.05) 

            # 2. Query Florence-2
            cv_img = data['cam0']
            _, buffer = cv2.imencode('.jpg', cv_img)
            img_bytes = buffer.tobytes()
            files = {'file': ('frame.jpg', img_bytes, 'image/jpeg')}
            
            try:
                # Get Caption
                resp_cap = requests.post(f"{self.api_url}/caption", files={'file': ('f.jpg', img_bytes, 'image/jpeg')}, data={'task': '<MORE_DETAILED_CAPTION>'})
                caption_text = resp_cap.json().get('result', '')
                
                # Get Labels
                resp_lab = requests.post(f"{self.api_url}/labels", files={'file': ('f.jpg', img_bytes, 'image/jpeg')}, data={'task': '<OD>'})
                labels_dict = resp_lab.json().get('result', {})
                labels_list = labels_dict.get('labels', [])

                # 3. Publish to Memory Nodes
                msg_cap = String()
                msg_cap.data = caption_text
                self.pub_caption.publish(msg_cap)

                if labels_list:
                    msg_lab = String()
                    msg_lab.data = json.dumps(labels_list)
                    self.pub_labels.publish(msg_lab)

                time.sleep(1.0) # Pause to prevent ROS 2 queue bloat

                # 4. Save for later usage (Memory population + ReMEmbR Question Formatter)
                filename = f"{timestamp}.pkl"
                captions_out.append({
                    "id": filename,
                    "file_start": filename,
                    "file_end": filename,
                    "time": timestamp,
                    "position": data['position'].tolist(),
                    "caption": caption_text,
                    "labels": labels_list 
                })    

                self.get_logger().info(f"Seq {seq_id} | Processed t={timestamp:.1f} | Labels: {len(labels_list)}")

            except Exception as e:
                self.get_logger().error(f"Florence API Error: {e}")

            # --- CRITICAL MEMORY CLEANUP FOR BATCH PROCESSING ---
            del data
            del cv_img
            del buffer
            del img_bytes
            gc.collect()

        # Save the captions JSON for this specific sequence
        out_dir = f"./data/captions/{seq_id}"
        os.makedirs(out_dir, exist_ok=True)
        
        # Save directly to the inner folder structure ReMEmbR expects
        # Changed filename slightly to reflect it contains labels too
        json_filename = f"{out_dir}/captions_Florence2-large_{int(self.time_interval)}_secs.json"
        
        with open(json_filename, 'w') as f:
            json.dump(captions_out, f, cls=NumpyEncoder, indent=4)
        
        self.get_logger().info(f"Playback Complete for Sequence {seq_id}. JSON saved to {json_filename}.")

def main(args=None):
    rclpy.init(args=args)
    node = CodaDatasetPlayer()
    rclpy.shutdown()

if __name__ == '__main__':
    main()