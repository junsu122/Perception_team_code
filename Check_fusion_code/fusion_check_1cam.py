import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from geometry_msgs.msg import PoseArray
import numpy as np
import cv2
from cv_bridge import CvBridge

class PointCloudToImage(Node):
    def __init__(self):
        super().__init__('pointcloud_to_image')

        # === 토픽 구독 ===
        # 카메라 원본 이미지
        self.image_subscription = self.create_subscription(
            Image,
            '/camera3/image_raw',
            self.image_callback,
            10
        )

        # 콘 포즈(PoseArray)
        self.posearray_subscription = self.create_subscription(
            PoseArray,
            '/cone_poses',
            self.cone_poses_callback,
            10
        )

        self.bridge = CvBridge()
        self.current_image = None

        ## center ##
        # self.RTLC = np.array([[0.0572, -0.9980, 0.0270, 0.0271],
        #                       [0.1006, -0.0211, -0.9947, -0.2647],
        #                       [0.9933, 0.0596, 0.0992, -0.1308]])
        
        # self.Mc = np.array([[600.0215532765091, 0.0, 328.4470315774296],
        #                     [0.0, 600.7558135485723, 236.1876388527033],
        #                     [0.0, 0.0, 1.0]])

        ## right ##
        self.RTLC = np.array([[-0.258213671681845, -0.964342407567990,  0.058046711556751, -0.246695652137148],
                               [-0.324116745139498,  0.029870691462926, -0.945545386172290, -0.119482435620032],
                               [ 0.910095618754842, -0.262966657121200, -0.320272543259242, -0.167583798275389]])

        self.Mc = np.array([[520.7113714280379, 0.0,               308.8513561709799],
                            [0.0,               521.4439302987403, 236.2402544548886],
                            [0.0,               0.0,               1.0]])

        ## left ##
        # self.RTLC = np.array([[0.363452501928163,	-0.931015506651510,	0.033352739266673,	0.218154602864188],
        #                        [-0.298642902093187,	-0.150347366693313,	-0.942447922358443,	-0.088227291598970],
        #                        [0.882448126447962,	0.332574496470819,	-0.332685299383161,	-0.044970737877070]])
        
        # self.Mc = np.array([[511.1833277232166,	0.0,	329.4307342734572],
        #                     [0.0,	514.3170736290211,	258.4781200652204],
        #                     [0.0,	0.0,	1.0]])


        # Projection Matrix 계산
        self.projection_matrix = np.dot(self.Mc, self.RTLC)
        self.get_logger().info(f'Projection Matrix: {self.projection_matrix}')

        # === 픽셀 보정 값 ===
        # 0929 center 보정
        # self.u_offset = -30
        # self.v_offset = -10

        # 0929 right 보정
        self.u_offset = -5
        self.v_offset = 80

        # 0929 left 보정
        # self.u_offset = -18
        # self.v_offset = 13

        self.output_path = '/home/junsu/Desktop/file'

    def image_callback(self, msg):
        self.current_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')

    def cone_poses_callback(self, msg: PoseArray):
        if self.current_image is None:
            self.get_logger().info('이미지를 아직 받지 못했습니다. 대기 중...')
            return

        points_3d = np.array([[p.position.x, p.position.y, p.position.z] for p in msg.poses], dtype=np.float32)
        if points_3d.size == 0:
            self.get_logger().warn('PoseArray에 포즈가 없습니다.')
            return

        projected_points = self.convert_3d_to_2d(points_3d)
        self.draw_points_on_image(projected_points)

        cv2.imwrite(self.output_path, self.current_image)
        self.get_logger().info(f'콘 포즈가 투영된 이미지를 저장했습니다: {self.output_path}')

    def convert_3d_to_2d(self, points_3d):
        ones = np.ones((points_3d.shape[0], 1), dtype=points_3d.dtype)
        points_h = np.hstack([points_3d, ones])
        proj = (self.projection_matrix @ points_h.T).T

        u = proj[:, 0] / proj[:, 2] + self.u_offset
        v = proj[:, 1] / proj[:, 2] + self.v_offset

        return list(zip(u, v))

    def draw_points_on_image(self, points):
        h, w = self.current_image.shape[:2]
        for u, v in points:
            if 0 <= u < w and 0 <= v < h:
                cv2.circle(self.current_image, (int(u), int(v)), radius=4, color=(0, 255, 0), thickness=-1)

def main(args=None):
    rclpy.init(args=args)
    node = PointCloudToImage()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
