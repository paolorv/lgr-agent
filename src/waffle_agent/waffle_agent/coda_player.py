import os
import glob
import json
import pickle as pkl
import time
import requests
import cv2
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseWithCovariance, TwistWithCovariance

class NumpyEncoder(json.JSONEncoder):
    def default(self, obj):
        import numpy as np
        if isinstance(obj, np.ndarray):
            return obj.tolist()
        return super(NumpyEncoder, self).default(obj)

class CodaDatasetPlayer(Node):
    def __init__(self):
        super().__init__('coda_dataset_player')
        
        self.declare_parameter('sequence_id', 6)
        self.declare_parameter('coda_data_dir', './coda_data')
        self.declare_parameter('florence_api', 'http://localhost:8001')
        self.declare_parameter('seconds_per_frame', 1.0) # Process 1 frame per second of sequence
        
        self.seq_id = self.get_parameter('sequence_id').value
        self.data_dir = self.get_parameter('coda_data_dir').value
        self.api_url = self.get_parameter('florence_api').value
        self.time_interval = self.get_parameter('seconds_per_frame').value

        # Publishers matching your memory nodes
        self.pub_odom1 = self.create_publisher(Odometry, '/odom', 10)       # For memory_builder_node
        self.pub_odom2 = self.create_publisher(Odometry, '/odometry', 10)   # For graphmemory_manager
        self.pub_caption = self.create_publisher(String, '/captions', 10)
        self.pub_labels = self.create_publisher(String, '/labels', 10)

        self.get_logger().info(f"Starting playback for Sequence {self.seq_id}")
        self.play_sequence()

    def play_sequence(self):
        pkl_files = glob.glob(os.path.join(self.data_dir, str(self.seq_id), '*.pkl'))
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
            # Set orientation from data['rotation'] here if needed
            
            self.pub_odom1.publish(odom_msg)
            self.pub_odom2.publish(odom_msg)
            time.sleep(0.05) # Brief pause to let subscribers register the pose

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

                time.sleep(1.0)   # SET SLEEP TO AVOID MEMORY LEAKS /!\

                # 4. Save for ReMEmbR Question Formatter
                #captions_out.append({
                #    "time": timestamp,
                #    "position": data['position'].tolist(),
                #    "caption": caption_text
                #})
                
                # 4. Save for ReMEmbR Question Formatter
                filename = f"{timestamp}.pkl"
                captions_out.append({
                    "id": filename,
                    "file_start": filename,
                    "file_end": filename,
                    "time": timestamp,
                    "position": data['position'].tolist(),
                    "caption": caption_text
                })    


                self.get_logger().info(f"Processed t={timestamp:.1f} | Labels: {len(labels_list)}")

            except Exception as e:
                self.get_logger().error(f"Florence API Error: {e}")

        # Save the captions JSON for form_question_jsons.py
        out_dir = f"./data/captions/{self.seq_id}"
        os.makedirs(out_dir, exist_ok=True)
        with open(f"{out_dir}/captions_Florence2-large_{int(self.time_interval)}_secs.json", 'w') as f:
            json.dump(captions_out, f, cls=NumpyEncoder, indent=4)
        
        self.get_logger().info("Playback Complete. Memory populated.")

def main(args=None):
    rclpy.init(args=args)
    node = CodaDatasetPlayer()
    rclpy.shutdown()

if __name__ == '__main__':
    main()