import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image

import cv2 
from cv_bridge import CvBridge

import socket
import struct
import pickle



class MinimalPublisher(Node):

    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(Image, 'camera_img', 10)
        timer_period = 1/30  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.sock.connect(('10.0.0.183', 9999))
            self.get_logger().info('✅ Connected to Pi TCP server')
        except Exception as e:
            self.get_logger().error(f'❌ Connection failed: {e}')

        self.bridge = CvBridge()


    def timer_callback(self):

        #self.get_logger().info(f'callback executed, iteration: {self.i}')

        length_bytes = self.sock.recv(4)
        #self.get_logger().info(f'made it past receive')

        if len(length_bytes) < 4:
            # handle incomplete read or disconnect
            #self.get_logger().info('Error: incomplete read')

            return
        
        #self.get_logger().info(f'unpacking bytes')
        length = struct.unpack(">L", length_bytes)[0]
        #self.get_logger().info(f'bytes upnpacked')

        data_bytes = b''

        #self.get_logger().info(f'Reading bytes')
        while len(data_bytes) < length:
            packet = self.sock.recv(length - len(data_bytes))
            if not packet:
                # client disconnected or error
                self.get_logger().info('error in unpacking bytes')

                return
            data_bytes += packet
        
        #self.get_logger().info(f'Bytes read')

        buffer = pickle.loads(data_bytes)

        frame = cv2.imdecode(buffer, cv2.IMREAD_COLOR)

        # Show the image in a window
        cv2.imshow("Preview", frame)
        cv2.waitKey(1)  # Needed to refresh the window

        ros_image = self.bridge.cv2_to_imgmsg(frame, encoding='bgr8')
        self.publisher_.publish(ros_image)

        self.i += 1


def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()