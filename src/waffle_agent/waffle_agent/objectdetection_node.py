import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import String
from cv_bridge import CvBridge
import cv2
import requests
import time
import json

# CONSOLE GRAPHICS
from rich.console import Console, Group
from rich.live import Live
from rich.markdown import Markdown
from rich.panel import Panel
from rich.text import Text

class ObjectDetectionClient(Node):
    def __init__(self):
        super().__init__('object_detection_client')
        self.bridge = CvBridge()
        
        # Latest available frame
        self.latest_cv_img = None
        #self.latest_pos= None
        #self.latest_time = None

        # CAPTION PUBLISHER
        self.publisher_ = self.create_publisher(String, '/labels', 10)

        # FRAME SUBSCRIPTION
        self.sub = self.create_subscription(
            Image, 
            '/zed/zed_node/rgb/color/rect/image', 
            self.img_callback, 
            10
        )
        
        # PROCESS MEMORY ITEM EVERY N SECONDS --> Callback posts to the memory server
        self.process_timer = self.create_timer(7.0, self.timer_callback)

        self.api_url = "http://localhost:8001/labels"
        self.get_logger().info("OD Client Started. Sending multipart/form-data requests...")


    def img_callback(self, msg):
        """Keep latest available frame."""
        try:
            self.latest_cv_img = self.bridge.imgmsg_to_cv2(msg, "bgr8")
        except Exception as e:
            self.get_logger().error(f"Frame conversion error: {e}")



#    def timer_callback(self):
#        """Encodes image to bytes and uploads via multipart/form-data."""
#        if self.latest_cv_img is None:
#            return

#        try:
#            cv_img = self.latest_cv_img
#            self.latest_cv_img = None # Prevent re-sending same frame if camera dies

            # JPEG buffer
#            _, buffer = cv2.imencode('.jpg', cv_img)
#            
#            # Get raw bytes from last frame
#            img_bytes = buffer.tobytes()

            # Configure request to send: image file, captioning task
#            files = {
#                'file': ('camera_frame.jpg', img_bytes, 'image/jpeg')
#            }
#            data = {
#                'task': '<OD>' # OBJECT DETECTION TASK
#            }

#            self.get_logger().info("Sending image to server...")
#            start = time.time()
            
            # Send POST using 'files=' parameter
#            response = requests.post(self.api_url, files=files, data=data)
#            latency = time.time() - start

#            if response.status_code == 200:
                # Parse result based on server's return: {"task":..., "result":...}
#                response_data = response.json()
#                raw_caption = response_data.get('result', 'No object labels found')
#                caption_msg = String() # Wrap in ROS2 String message
#                caption_msg.data = raw_caption
#                self.get_logger().info(f"Ref: {latency:.2f}s | Result: {raw_caption}")

                # PUBLISH CAPTION: NOT USED HERE
                #self.publisher_.publish(caption_msg)
                #self.get_logger().info(f'POSTED TO /captions TOPIC')
#            else:
#                self.get_logger().error(f"Server Error {response.status_code}: {response.text}")

#        except Exception as e:
#            self.get_logger().error(f"Request failed: {e}")

    def timer_callback(self):
        """Encodes image to bytes and uploads via multipart/form-data."""
        if self.latest_cv_img is None:
            return

        try:
            cv_img = self.latest_cv_img
            self.latest_cv_img = None 

            _, buffer = cv2.imencode('.jpg', cv_img)
            img_bytes = buffer.tobytes()

            files = {'file': ('camera_frame.jpg', img_bytes, 'image/jpeg')}
            data = {'task': '<DENSE_REGION_CAPTION>'} ###CHANGE BASED ON THE TASK!

            self.get_logger().info("Sending image to server...")
            start = time.time()
            response = requests.post(self.api_url, files=files, data=data)
            latency = time.time() - start

            if response.status_code == 200:
                response_data = response.json()
                
                # Extract the labels array from the nested JSON
                # E.g., ["car", "wheel", "wheel"]
                result_dict = response_data.get('result', {})
                labels_list = result_dict.get('labels', [])

                if labels_list:  # Only publish if objects were actually detected
                    labels_msg = String()
                    # Convert the Python list to a JSON-formatted string
                    labels_msg.data = json.dumps(labels_list) #### CHECK CONVERSION ############
                    
                    self.publisher_.publish(labels_msg)
                    #self.get_logger().info(f"Ref: {latency:.2f}s | Published labels: {labels_list}")

                    formatted_list = "\n".join([f"• {item}\n" for item in labels_list])
                    self.print_stream(''.join(formatted_list))
                #else:
                    #self.get_logger().info(f"Ref: {latency:.2f}s | No objects detected.")

            else:
                self.get_logger().error(f"Server Error {response.status_code}: {response.text}")

        except Exception as e:
            self.get_logger().error(f"Request failed: {e}")


    def print_stream(self, text):
        console = Console()
        with Live(console=console, auto_refresh=True, vertical_overflow="visible") as live:
            content_panel = Panel(Markdown(text), title="Detected entities", border_style="blue")
            live.update(content_panel, refresh=True)

def main():
    rclpy.init()
    node = ObjectDetectionClient()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()




##### Important to handle multiple observations of the same object
