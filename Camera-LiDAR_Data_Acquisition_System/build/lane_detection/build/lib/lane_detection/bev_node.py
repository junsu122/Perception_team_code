#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import numpy as np

class BirdViewNode(Node):
    def __init__(self):
        super().__init__('bird_view_node')
        self.bridge = CvBridge()

        self.sub = self.create_subscription(
            Image,
            '/camera1/image_raw',
            self.image_callback,
            10
        )
        self.pub = self.create_publisher(Image, '/camera1/image_birdview', 10)

        # 투시변환에 사용할 포인트 (카메라 위치에 맞게 수동 설정 필요)
        self.src_pts = np.float32([[200, 320], [440, 320], [640, 480], [0, 480]])
        self.dst_pts = np.float32([[0, 0], [640, 0], [640, 480], [0, 480]])

    def image_callback(self, msg):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except Exception as e:
            self.get_logger().error(f"CV Bridge Error: {e}")
            return

        # BEV 변환
        M = cv2.getPerspectiveTransform(self.src_pts, self.dst_pts)
        bev_image = cv2.warpPerspective(cv_image, M, (640, 480))

        bev_msg = self.bridge.cv2_to_imgmsg(bev_image, encoding='bgr8')
        bev_msg.header = msg.header
        self.pub.publish(bev_msg)

def main(args=None):
    rclpy.init(args=args)
    node = BirdViewNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

