import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import String
from cv_bridge import CvBridge
import cv2
import requests
import time


class VILACaptionerClient(Node):
    def __init__(self):
        super().__init__('vila_captioner_client')
        self.bridge = CvBridge()
        
        # Latest available frame
        self.latest_cv_img = None
        #self.latest_pos= None
        #self.latest_time = None

        # CAPTION PUBLISHER
        self.publisher_ = self.create_publisher(String, '/captions', 10)

        # FRAME SUBSCRIPTION
        self.sub = self.create_subscription(
            Image, 
            '/camera/image_raw', 
            self.img_callback, 
            10
        )
        
        # PROCESS MEMORY ITEM EVERY N SECONDS --> Callback posts to the memory server
        self.process_timer = self.create_timer(7.0, self.timer_callback)

        self.api_url = "http://localhost:8001/caption"
        self.get_logger().info("VILA Client Started. Sending multipart/form-data requests...")


    def img_callback(self, msg):
        """Keep latest available frame."""
        try:
            self.latest_cv_img = self.bridge.imgmsg_to_cv2(msg, "bgr8")
        except Exception as e:
            self.get_logger().error(f"Frame conversion error: {e}")



    def timer_callback(self):
        """Encodes image to bytes and uploads via multipart/form-data."""
        if self.latest_cv_img is None:
            return

        try:
            cv_img = self.latest_cv_img
            self.latest_cv_img = None # Prevent re-sending same frame if camera dies

            # JPEG buffer
            _, buffer = cv2.imencode('.jpg', cv_img)
            
            # Get raw bytes from last frame
            img_bytes = buffer.tobytes()

            # Configure request to send: image file, captioning task
            files = {
                'file': ('camera_frame.jpg', img_bytes, 'image/jpeg')
            }
            data = {
                'task': '<MORE_DETAILED_CAPTION>' # Most detailed captioning task preset available on the model
            }

            self.get_logger().info("Sending image to server...")
            start = time.time()
            
            # Send POST using 'files=' parameter
            response = requests.post(self.api_url, files=files, data=data)
            latency = time.time() - start

            if response.status_code == 200:
                # Parse result based on your server's return: {"task":..., "result":...}
                response_data = response.json()
                raw_caption = response_data.get('result', 'No caption found')
                caption_msg = String() # Wrap in ROS2 String message
                caption_msg.data = raw_caption
                self.get_logger().info(f"Ref: {latency:.2f}s | Result: {raw_caption}")

                # PUBLISH CAPTION
                self.publisher_.publish(caption_msg)
                self.get_logger().info(f'POSTED TO /captions TOPIC')
            else:
                self.get_logger().error(f"Server Error {response.status_code}: {response.text}")

        except Exception as e:
            self.get_logger().error(f"Request failed: {e}")

def main():
    rclpy.init()
    node = VILACaptionerClient()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()