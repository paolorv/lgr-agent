import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import base64
import requests
import time

class VILACaptionerClient(Node):
    def __init__(self):
        super().__init__('vila_captioner_client')
        self.bridge = CvBridge()
        self.sub = self.create_subscription(Image, '/camera/image_raw', self.img_callback, 10)
        
        # Point this to your VILA container IP
        # If running on same machine, use "localhost" or "host.docker.internal"
        self.api_url = "http://localhost:8001/v1/chat/completions"
        self.get_logger().info("VILA Client Node Started. Waiting for images...")

    def encode_image(self, cv_img):
        """Encodes OpenCV image to Base64 string"""
        _, buffer = cv2.imencode('.jpg', cv_img)
        return base64.b64encode(buffer).decode('utf-8')

    def img_callback(self, msg):
        try:
            cv_img = self.bridge.imgmsg_to_cv2(msg, "bgr8")
            b64_image = self.encode_image(cv_img)

            payload = {
                "model": "Efficient-Large-Model/VILA1.5-3b",
                "messages": [
                    {
                        "role": "user",
                        "content": [
                            {"type": "text", "text": "Describe this image in detail."},
                            {
                                "type": "image_url",
                                "image_url": {"url": f"data:image/jpeg;base64,{b64_image}"}
                            }
                        ]
                    }
                ],
                "max_tokens": 100
            }

            self.get_logger().info("Sending request to VILA...")
            
            # Send HTTP POST
            start = time.time()
            response = requests.post(self.api_url, json=payload)
            latency = time.time() - start

            if response.status_code == 200:
                result = response.json()
                caption = result['choices'][0]['message']['content']
                self.get_logger().info(f"Ref: {latency:.2f}s | VILA: {caption}")
            else:
                self.get_logger().error(f"Error {response.status_code}: {response.text}")

        except Exception as e:
            self.get_logger().error(f"Failed to process image: {e}")

def main():
    rclpy.init()
    node = VILACaptionerClient()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()