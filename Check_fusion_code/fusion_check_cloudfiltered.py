import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, PointCloud2
from sensor_msgs_py import point_cloud2 as pc2
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
            '/camera1/image_raw',
            self.image_callback,
            10
        )

        # PointCloud 구독
        self.pointcloud_subscription = self.create_subscription(
            PointCloud2,
            '/cloud_filtered',
            self.pointcloud_callback,
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
        
        
        #  backup_1001
        self.RTLC = np.array([[0.363452501928163,	-0.931015506651510,	0.033352739266673,	0.218154602864188],
                    [-0.298642902093187,	-0.150347366693313,	-0.942447922358443,	-0.088227291598970],
                     [0.882448126447962,	0.332574496470819,	-0.332685299383161,	-0.044970737877070]])  
        
        self.Mc = np.array([[511.1833277232166,	0.0,	329.4307342734572],
                             [0.0,	514.3170736290211,	258.4781200652204],
                             [0.0,	0.0,	1.0]]) 

        # new 1001
        # self.RTLC = np.array([[0.350746733058141,	-0.936407468974379,	0.010852709248787,	0.206457091803382],
        #                     [-0.307809278461130,	-0.126224555839665,	-0.943038074308942,	-0.030000293038297],
        #                     [0.884437774714694,	0.327426959110085,	-0.332507757963094,	0.023725181925089]])  
        

        # self.Mc = np.array([[525.7954212416450,	0.0,	329.9293094774995],
        #                     [0.0,	528.6428427519203,	249.0554413135177],
        #                     [0.0,	0.0,	1.0]]) 


        # Projection Matrix 계산
        self.projection_matrix = np.dot(self.Mc, self.RTLC)
        self.get_logger().info(f'Projection Matrix: {self.projection_matrix}')

        # === 픽셀 보정 값 ===
        # center
        # self.u_offset = -30
        # self.v_offset = -10

        self.u_offset = -18
        self.v_offset = 13

        self.output_path = '/home/acca/all/Perception/fusion_check/output_image.png'

    def image_callback(self, msg):
        self.current_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')

    def pointcloud_callback(self, msg: PointCloud2):
        if self.current_image is None:
            self.get_logger().info('이미지를 아직 받지 못했습니다. 대기 중...')
            return

        # PointCloud2 → numpy array
        points = []
        for p in pc2.read_points(msg, field_names=("x", "y", "z"), skip_nans=True):
            points.append([p[0], p[1], p[2]])
        points_3d = np.array(points, dtype=np.float32)

        if points_3d.size == 0:
            self.get_logger().warn('PointCloud2에 유효한 포인트가 없습니다.')
            return

        projected_points = self.convert_3d_to_2d(points_3d)
        self.draw_points_on_image(projected_points)

        cv2.imwrite(self.output_path, self.current_image)
        self.get_logger().info(f'포인트클라우드가 투영된 이미지를 저장했습니다: {self.output_path}')

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
