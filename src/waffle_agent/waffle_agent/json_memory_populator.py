import os
import json
import time
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from nav_msgs.msg import Odometry

class JsonMemoryPopulator(Node):
    def __init__(self):
        super().__init__('json_memory_populator')
        
        # Parameters
        self.declare_parameter('json_path', './data/captions/0/captions_Florence2-large_2_secs.json')
        self.declare_parameter('publish_delay', 0.1) 
        
        self.json_path = self.get_parameter('json_path').value
        self.delay = self.get_parameter('publish_delay').value

        # Publishers
        self.pub_odom1 = self.create_publisher(Odometry, '/odom', 10)
        self.pub_odom2 = self.create_publisher(Odometry, '/odometry', 10)
        self.pub_caption = self.create_publisher(String, '/captions', 10)
        self.pub_labels = self.create_publisher(String, '/labels', 10) # Graph manager listens here

        self.get_logger().info(f"Loading data from: {self.json_path}")
        self.spool_data()

    def spool_data(self):
        if not os.path.exists(self.json_path):
            self.get_logger().error(f"JSON file not found: {self.json_path}")
            return

        with open(self.json_path, 'r') as f:
            data = json.load(f)

        self.get_logger().info(f"Found {len(data)} frames. Spooling to memory backends using DLABELS...")

        for item in data:
            # # 1. Publish Odometry
            # odom_msg = Odometry()
            # odom_msg.header.stamp = self.get_clock().now().to_msg()
            # odom_msg.header.frame_id = "map"
            # 1. Publish Odometry with HISTORICAL time
            hist_time_sec = float(item['time'])
            
            odom_msg = Odometry()
            odom_msg.header.stamp.sec = int(hist_time_sec)
            odom_msg.header.stamp.nanosec = int((hist_time_sec - int(hist_time_sec)) * 1e9)
            odom_msg.header.frame_id = "map"
            odom_msg.pose.pose.position.x = float(item['position'][0])
            odom_msg.pose.pose.position.y = float(item['position'][1])
            odom_msg.pose.pose.position.z = float(item['position'][2])
            
            self.pub_odom1.publish(odom_msg)
            self.pub_odom2.publish(odom_msg)
            time.sleep(0.05) 

            # 2. Publish Caption
            msg_cap = String()
            msg_cap.data = item.get('caption', '')
            self.pub_caption.publish(msg_cap)

            # 3. Publish Dense Labels (dlabels) instead of standard labels
            dlabels = item.get('dlabels', [])
            if dlabels:
                msg_lab = String()
                msg_lab.data = json.dumps(dlabels)
                self.pub_labels.publish(msg_lab)

            self.get_logger().info(f"Published Memory Node at t={item['time']} | Dlabels: {len(dlabels)}")
            time.sleep(self.delay)

        self.get_logger().info("Finished populating memory databases!")

def main(args=None):
    rclpy.init(args=args)
    node = JsonMemoryPopulator()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()