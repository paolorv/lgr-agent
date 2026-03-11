import os
import json
import time
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from nav_msgs.msg import Odometry

class JsonMemorySpooler(Node):
    def __init__(self):
        super().__init__('json_memory_spooler')
        
        # Parameters
        self.declare_parameter('json_path', './data/captions/0/captions_Florence2-large_1_secs.json')
        self.declare_parameter('publish_delay', 0.2) # Wait 0.2s between frames so graph DB doesn't choke
        
        self.json_path = self.get_parameter('json_path').value
        self.delay = self.get_parameter('publish_delay').value

        # Publishers (Matching your memory nodes)
        self.pub_odom1 = self.create_publisher(Odometry, '/odom', 10)
        self.pub_odom2 = self.create_publisher(Odometry, '/odometry', 10)
        self.pub_caption = self.create_publisher(String, '/captions', 10)
        self.pub_labels = self.create_publisher(String, '/labels', 10)

        self.get_logger().info(f"Loading data from: {self.json_path}")
        self.spool_data()

    def spool_data(self):
        if not os.path.exists(self.json_path):
            self.get_logger().error("JSON file not found!")
            return

        with open(self.json_path, 'r') as f:
            data = json.load(f)

        self.get_logger().info(f"Found {len(data)} frames. Spooling to memory backends...")

        for item in data:
            # 1. Publish Odometry
            odom_msg = Odometry()
            odom_msg.header.stamp = self.get_clock().now().to_msg()
            odom_msg.header.frame_id = "map"
            odom_msg.pose.pose.position.x = float(item['position'][0])
            odom_msg.pose.pose.position.y = float(item['position'][1])
            odom_msg.pose.pose.position.z = float(item['position'][2])
            
            self.pub_odom1.publish(odom_msg)
            self.pub_odom2.publish(odom_msg)
            
            time.sleep(0.05) # Brief pause to let nodes register the pose

            # 2. Publish Caption
            msg_cap = String()
            msg_cap.data = item['caption']
            self.pub_caption.publish(msg_cap)

            # 3. Publish Labels
            if 'labels' in item and item['labels']:
                msg_lab = String()
                msg_lab.data = json.dumps(item['labels'])
                self.pub_labels.publish(msg_lab)

            self.get_logger().info(f"Published Memory Node at t={item['time']}")
            time.sleep(self.delay)

        self.get_logger().info("Finished populating memory databases!")

def main(args=None):
    rclpy.init(args=args)
    node = JsonMemorySpooler()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()