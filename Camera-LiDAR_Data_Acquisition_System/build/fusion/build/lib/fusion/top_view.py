#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, CompressedImage
from visualization_msgs.msg import Marker, UVCoordinate
from geometry_msgs.msg import Point
from cv_bridge import CvBridge
import cv2
import numpy as np

class VideoProjector(Node):
    def __init__(self):
        super().__init__('video_projector')
        self.bridge = CvBridge()
        self.subscriber = self.create_subscription(
            Image,
            'camera1/image_raw',
            self.image_callback,
            10
        )
        self.publisher = self.create_publisher(Marker, 'projected_video', 10)

        self.declare_parameter('bottom_left_x', 0.0)
        self.declare_parameter('bottom_left_y', -2.0)
        self.declare_parameter('bottom_left_z', 0.0)
        self.declare_parameter('proj_width', 4.0)
        self.declare_parameter('proj_height', 3.0)

    def image_callback(self, msg: Image):
        bottom_left_x = self.get_parameter('bottom_left_x').value
        bottom_left_y = self.get_parameter('bottom_left_y').value
        bottom_left_z = self.get_parameter('bottom_left_z').value
        proj_width = self.get_parameter('proj_width').value
        proj_height = self.get_parameter('proj_height').value

        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except Exception as e:
            self.get_logger().error(f"이미지 변환 오류: {e}")
            return

        ret, buffer = cv2.imencode('.jpg', cv_image)
        if not ret:
            self.get_logger().error("이미지 압축 실패")
            return
        comp_img = CompressedImage()
        comp_img.header = msg.header
        comp_img.format = "jpeg"
        comp_img.data = buffer.tobytes()

        bottom_left = np.array([bottom_left_x, bottom_left_y, bottom_left_z])
        bottom_right = bottom_left + np.array([proj_width, 0.0, 0.0])
        top_right = bottom_left + np.array([proj_width, proj_height, 0.0])
        top_left = bottom_left + np.array([0.0, proj_height, 0.0])

        marker = Marker()
        marker.header.frame_id = "velodyne"
        marker.header.stamp = self.get_clock().now().to_msg()
        marker.ns = "video_projection"
        marker.id = 0
        marker.type = Marker.TRIANGLE_LIST
        marker.action = Marker.ADD
        marker.pose.orientation.w = 1.0

        pts = [bottom_left, bottom_right, top_right,
               bottom_left, top_right, top_left]
        for pt in pts:
            p = Point()
            p.x, p.y, p.z = float(pt[0]), float(pt[1]), float(pt[2])
            marker.points.append(p)

        # 수정된 uv_coordinates 할당 (UVCoordinate 타입 사용)
        uv_coords = [(0.0, 0.0), (1.0, 0.0), (1.0, 1.0),
                     (0.0, 0.0), (1.0, 1.0), (0.0, 1.0)]
        marker.uv_coordinates = []
        for uv in uv_coords:
            uv_msg = UVCoordinate()
            uv_msg.u = uv[0]
            uv_msg.v = uv[1]
            marker.uv_coordinates.append(uv_msg)

        marker.texture = comp_img
        marker.texture_resource = ""
        marker.scale.x = 1.0
        marker.scale.y = 1.0
        marker.scale.z = 1.0
        marker.color.r = 1.0
        marker.color.g = 1.0
        marker.color.b = 1.0
        marker.color.a = 1.0

        self.publisher.publish(marker)

def main(args=None):
    rclpy.init(args=args)
    node = VideoProjector()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
