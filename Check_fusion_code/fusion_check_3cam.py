#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
import cv2
import numpy as np
from cv_bridge import CvBridge
from sensor_msgs.msg import Image
from geometry_msgs.msg import PoseArray

class ProjectionNode(Node):
    def __init__(self):
        super().__init__('projection_node')

        # Subscribers
        self.pose_sub = self.create_subscription(PoseArray, '/cone_poses', self.pose_callback, 10)
        self.image_sub = self.create_subscription(Image, '/concated_cam', self.image_callback, 10)

        # Publisher
        self.image_pub = self.create_publisher(Image, 'projection_img', 10)

        self.bridge = CvBridge()
        self.latest_image = None

        # --- Calibration Matrices ---
        self.L_RTlc = np.array([
            [0.363452501928163, -0.931015506651510, 0.033352739266673, 0.218154602864188],
            [-0.298642902093187, -0.150347366693313, -0.942447922358443, -0.088227291598970],
            [0.882448126447962, 0.332574496470819, -0.332685299383161, -0.044970737877070],
            [0.0, 0.0, 0.0, 1.0]
        ])
        self.L_Mc = np.array([
            [511.1833277232166, 0.0, 329.4307342734572, 0.0],
            [0.0, 514.3170736290211, 258.4781200652204, 0.0],
            [0.0, 0.0, 1.0, 0.0]
        ])

        self.C_RTlc = np.array([
            [0.0572, -0.9980, 0.0270, 0.0271],
            [0.1006, -0.0211, -0.9947, -0.2647],
            [0.9933, 0.0596, 0.0992, -0.1308],
            [0.0, 0.0, 0.0, 1.0]
        ])
        self.C_Mc = np.array([
            [600.0215532765091, 0.0, 328.4470315774296, 0.0],
            [0.0, 600.7558135485723, 236.1876388527033, 0.0],
            [0.0, 0.0, 1.0, 0.0]
        ])

        self.R_RTlc = np.array([
            [-0.258213671681845, -0.964342407567990, 0.058046711556751, -0.246695652137148],
            [-0.324116745139498, 0.029870691462926, -0.945545386172290, -0.119482435620032],
            [0.910095618754842, -0.262966657121200, -0.320272543259242, -0.167583798275389],
            [0.0, 0.0, 0.0, 1.0]
        ])
        self.R_Mc = np.array([
            [520.7113714280379, 0.0, 308.8513561709799, 0.0],
            [0.0, 521.4439302987403, 236.2402544548886, 0.0],
            [0.0, 0.0, 1.0, 0.0]
        ])

        self.L_result = self.L_Mc @ self.L_RTlc
        self.C_result = self.C_Mc @ self.C_RTlc
        self.R_result = self.R_Mc @ self.R_RTlc

        # --- Pixel correction offsets (dx, dy) ---
        self.offset_L = (0, 0)
        self.offset_C = (0, 0)
        self.offset_R = (0, 0)

    def image_callback(self, msg):
        self.latest_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")

    def pose_callback(self, msg):
        if self.latest_image is None:
            return
        
        img = self.latest_image.copy()

        for pose in msg.poses:
            p = np.array([pose.position.x, pose.position.y, pose.position.z, 1.0])

            # 각 카메라에 투영 (concated_cam에서 L=0, C=640, R=1280 기준)
            proj_L = self.project_point(p, self.L_result, (0,0), self.offset_L)
            proj_C = self.project_point(p, self.C_result, (640,0), self.offset_C)
            proj_R = self.project_point(p, self.R_result, (1280,0), self.offset_R)

            for pt in [proj_L, proj_C, proj_R]:
                if pt is not None:
                    cv2.circle(img, pt, 5, (0,0,255), -1)  # 빨간 점

        proj_msg = self.bridge.cv2_to_imgmsg(img, "bgr8")
        proj_msg.header = msg.header
        self.image_pub.publish(proj_msg)

    def project_point(self, point, proj_matrix, base_offset=(0,0), correction=(0,0)):
        cam = proj_matrix @ point
        if cam[2] <= 0:
            return None
        cam /= cam[2]
        
        # 기본 오프셋 (concated_cam 위치) + 보정 오프셋
        x = int(cam[0] + base_offset[0] + correction[0])
        y = int(cam[1] + base_offset[1] + correction[1])

        if 0 <= x < 1920 and 0 <= y < 480:  # concated_cam 크기 가정
            return (x,y)
        return None

def main(args=None):
    rclpy.init(args=args)
    node = ProjectionNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
