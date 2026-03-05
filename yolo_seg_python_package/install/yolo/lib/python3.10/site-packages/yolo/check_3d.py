import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseArray, PointStamped
from yolo_msg.msg import BoundingBoxArray
import numpy as np


class FusionNode(Node):
    def __init__(self):
        super().__init__('single_camera_lidar_fusion')

        # Subscribers
        self.cone_sub = self.create_subscription(
            PoseArray,
            '/cone_poses',
            self.cone_pose_callback,
            10
        )
        self.box_sub = self.create_subscription(
            BoundingBoxArray,
            '/bounding_box',
            self.bounding_boxes_callback,
            10
        )

        # Publishers
        self.yellow_pub = self.create_publisher(PointStamped, 'point/yellow', 10)
        self.blue_pub = self.create_publisher(PointStamped, 'point/blue', 10)
        self.check_pixel_pub = self.create_publisher(PointStamped, 'check_pixel', 10)  # 추가

        ################## Center#######################
        self.Mc_center = np.array([
            [600.0215532765091, 0.0,  328.4470315774296, 0.0],
            [0.0, 600.7558135485723, 236.1876388527033, 0.0],
            [0.0, 0.0,  1.0, 0.0]
        ])

        self.RTlc_center = np.array([
            [0.0572, -0.9980, 0.0270,  0.0271],
            [0.1006, -0.0211, -0.9947, -0.2647],
            [0.9933,  0.0596, -0.0992, -0.1308],
            [0.0,     0.0,     0.0,     1.0]
        ])

        self.M_result_ = self.Mc_center @ self.RTlc_center
        self.boxes_ = None



import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseArray, PointStamped
from yolo_msg.msg import BoundingBoxArray
import numpy as np


class FusionNode(Node):
    def __init__(self):
        super().__init__('single_camera_lidar_fusion')

        # Subscribers
        self.cone_sub = self.create_subscription(
            PoseArray,
            '/cone_poses',
            self.cone_pose_callback,
            10
        )
        self.box_sub = self.create_subscription(
            BoundingBoxArray,
            '/bounding_box',
            self.bounding_boxes_callback,
            10
        )

        # Publishers
        self.yellow_pub = self.create_publisher(PointStamped, 'point/yellow', 10)
        self.blue_pub = self.create_publisher(PointStamped, 'point/blue', 10)
        self.check_pixel_pub = self.create_publisher(PointStamped, 'check_pixel', 10)  # ✅ RViz 확인용

        ################## Center Camera #######################
        self.Mc_center = np.array([
            [600.0215532765091, 0.0,  328.4470315774296, 0.0],
            [0.0, 600.7558135485723, 236.1876388527033, 0.0],
            [0.0, 0.0,  1.0, 0.0]
        ])

        self.RTlc_center = np.array([
            [0.0572, -0.9980, 0.0270,  0.0271],
            [-0.298642902093187, -0.150347366693313, -0.942447922358443, -0.088227291598970],
            [0.882448126447962, 0.332574496470819, -0.332685299383161, -0.044970737877070],
            [0.0,     0.0,     0.0,     1.0]
        ])

        ##################### Left#######################
        # self.Mc_left = np.array([
        #     [6511.1833277232166,	0.0,	329.4307342734572, 0.0],
        #     [0.0,	514.3170736290211,	258.4781200652204, 0.0],
        #     [0.0,	0.0,	1.0, 0.0]
        # ])
        # self.RTlc_left = np.array([
        #     [0.363452501928163,	-0.931015506651510,	0.033352739266673,	0.218154602864188],
        #     [-0.298642902093187,	-0.150347366693313,	-0.942447922358443,	-0.088227291598970],
        #     [0.882448126447962,	0.332574496470819,	-0.332685299383161,	-0.044970737877070],
        #     [0.0,	0.0,	0.0,	1.000000000000000]
        # ])


        ##################### Right########################
        # self.Mc_right = np.array([
        #     [520.7113714280379,	0.0,	 308.8513561709799, 0.0],
        #     [0.0,	521.4439302987403,	236.2402544548886, 0.0],
        #     [0.0,	0.0,	1.0, 0.0]
        # ])
        # self.RTlc_right = np.array([
        #     [-0.258213671681845, -0.964342407567990, 0.058046711556751, -0.246695652137148],
        #     [-0.324116745139498, 0.029870691462926, -0.945545386172290, -0.119482435620032],
        #     [0.910095618754842, -0.262966657121200, -0.320272543259242, -0.167583798275389],
        #     [0.0, 0.0, 0.0, 1.0]
        # ])

        self.latest_cone_poses = None
        self.latest_boxes = None

    def publish_check_pixel(self, lidar_homo, header):
        """LiDAR 좌표계로 변환한 점을 /check_pixel로 발행"""
        point_msg = PointStamped()
        point_msg.header = header
        point_msg.header.frame_id = "velodyne"
        xyz = lidar_homo[:3] / lidar_homo[3]
        point_msg.point.x = float(xyz[0])
        point_msg.point.y = float(xyz[1])
        point_msg.point.z = float(xyz[2])
        self.check_pixel_pub.publish(point_msg)

    def cone_pose_callback(self, msg: PoseArray):
        """LiDAR 포인트 → 카메라 좌표 변환 후, 마지막 받은 바운딩박스와 매칭"""
        self.latest_cone_poses = msg
        if self.latest_boxes:
            self.process_boxes_with_cones()

    def bounding_boxes_callback(self, msg: BoundingBoxArray):
        """YOLO 바운딩박스 저장 후, 최근 LiDAR 포인트와 함께 처리"""
        self.latest_boxes = msg
        if self.latest_cone_poses:
            self.process_boxes_with_cones()

    def process_boxes_with_cones(self):
        """cone_poses와 bounding box를 이용해 픽셀 중심을 LiDAR 좌표로 변환"""
        if not self.latest_cone_poses or not self.latest_boxes:
            return

        # Intrinsic (3x3) 역행렬 계산
        K = self.Mc_center[:, :3]  # 카메라 내부 파라미터
        K_inv = np.linalg.inv(K)

        for pose in self.latest_cone_poses.poses:
            # LiDAR → 카메라 좌표
            velodyne_point = np.array([pose.position.x, pose.position.y, pose.position.z, 1.0])
            M_result = self.Mc_center @ self.RTlc_center
            # M_result = self.Mc_left @ self.RTlc_left
            # M_result = self.Mc_right @ self.RTlc_right
            projected = M_result @ velodyne_point

            depth = projected[2]  # 카메라 Z축 거리 (scale factor)
            if depth <= 0:
                continue  # 카메라 뒤에 있는 포인트는 제외

            norm_proj = projected / depth
            u_proj, v_proj = norm_proj[0], norm_proj[1]

            for box in self.latest_boxes.boxes:
                xmin = box.x
                xmax = xmin + box.width
                ymin = box.y
                ymax = ymin + box.height

                if xmin <= u_proj <= xmax and ymin <= v_proj <= ymax:
                    # YOLO 바운딩박스 중심 좌표
                    u_center = box.pixel_center_x
                    v_center = box.pixel_center_y

                    # (1) 픽셀 좌표 * depth → 카메라 좌표
                    pixel_h = np.array([u_center, v_center, 1.0])
                    cam_xyz = K_inv @ (pixel_h * depth)

                    # (2) 동차좌표로 변환
                    cam_homo = np.array([cam_xyz[0], cam_xyz[1], cam_xyz[2], 1.0])

                    # (3) 카메라 → LiDAR 좌표 변환
                    RTlc_inv = np.linalg.inv(self.RTlc_center)
                    reproj_lidar = RTlc_inv @ cam_homo

                    # 퍼블리시
                    self.publish_check_pixel(reproj_lidar, self.latest_cone_poses.header)

        # 데이터 초기화
        self.latest_cone_poses = None
        self.latest_boxes = None


def main(args=None):
    rclpy.init(args=args)
    node = FusionNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()

