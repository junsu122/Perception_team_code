import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2, Image
import numpy as np
import open3d as o3d
import cv2
from cv_bridge import CvBridge
import struct
from math import isnan
import os

def _get_struct_fmt(is_bigendian, fields, field_names=None):
    fmt = '>' if is_bigendian else '<'
    offset = 0
    for field in sorted(fields, key=lambda f: f.offset):
        while offset < field.offset:
            fmt += 'x'
            offset += 1
        if field_names is None or field.name in field_names:
            if field.datatype == 1:  # INT8
                fmt += 'b'
                offset += 1
            elif field.datatype == 2:  # UINT8
                fmt += 'B'
                offset += 1
            elif field.datatype == 3:  # INT16
                fmt += 'h'
                offset += 2
            elif field.datatype == 4:  # UINT16
                fmt += 'H'
                offset += 2
            elif field.datatype == 5:  # INT32
                fmt += 'i'
                offset += 4
            elif field.datatype == 6:  # UINT32
                fmt += 'I'
                offset += 4
            elif field.datatype == 7:  # FLOAT32
                fmt += 'f'
                offset += 4
            elif field.datatype == 8:  # FLOAT64
                fmt += 'd'
                offset += 8
            else:
                raise Exception('Unknown PointField datatype [%d]' % field.datatype)
        else:
            fmt += 'x' * field.count
            offset += field.count
    return fmt

class PointCloudSaver(Node):

    def __init__(self):
        super().__init__('pointcloud_saver')
        
        # 파일 저장 순서 번호
        self.file_index = 1
        self.folder_path = "/home/junsu/1.cam/src/fusion/fusion/file1"  # 현재 폴더에 저장
        
        # LiDAR PointCloud2 토픽 구독
        self.subscription_pc = self.create_subscription(
            PointCloud2,
            '/cropbox_filtered',  # LiDAR 데이터 토픽 이름
            self.pointcloud_callback,
            10)
        
        # Camera Image 토픽 구독
        self.subscription_img = self.create_subscription(
            Image,
            '/camera1/image_raw',  # 카메라 이미지 토픽 이름
            self.image_callback,
            10)
        
        self.latest_cloud = None
        self.latest_image = None
        self.bridge = CvBridge()

        # 5초마다 저장 실행
        self.timer = self.create_timer(5.0, self.timer_callback)

        # 이모지 카운터 및 방향 플래그
        self.emoji_count = 1
        self.emoji_direction = 1

    def pointcloud_callback(self, msg):
        """ 최신 LiDAR 포인트 클라우드 저장 """
        self.latest_cloud = msg

    def image_callback(self, msg):
        """ 최신 카메라 이미지 저장 """
        self.latest_image = msg

    def timer_callback(self):
        """ 5초마다 LiDAR와 카메라 데이터를 같은 번호로 저장 """
        if self.latest_cloud is not None and self.latest_image is not None:
            # 이모지 패턴 업데이트
            emoji = "🌟" * self.emoji_count

            # 이모지 카운터 변경
            self.emoji_count += self.emoji_direction
            if self.emoji_count == 5:
                self.emoji_direction = -1
            elif self.emoji_count == 1:
                self.emoji_direction = 1

            self.save_data(self.latest_cloud, self.latest_image, emoji)

    def save_data(self, cloud_msg, img_msg, emoji):
        """ LiDAR PointCloud2와 카메라 이미지를 같은 시간에 저장 """
        filename_pcd = os.path.join(self.folder_path, f"{self.file_index}.pcd")
        filename_img = os.path.join(self.folder_path, f"{self.file_index}.jpg")

        # PointCloud 저장
        points = np.array(list(self.read_points(cloud_msg, field_names=("x", "y", "z"), skip_nans=True)))
        cloud = o3d.geometry.PointCloud()
        cloud.points = o3d.utility.Vector3dVector(points)
        o3d.io.write_point_cloud(filename_pcd, cloud)

        # Image 저장
        image = self.bridge.imgmsg_to_cv2(img_msg, "bgr8")
        cv2.imwrite(filename_img, image)

        # 로그 출력 (이모지 증가 패턴 포함)
        self.get_logger().info(f"{emoji} [SAVED] PointCloud: {filename_pcd} {emoji}")
        self.get_logger().info(f"{emoji} [SAVED] Image: {filename_img} {emoji}")

        # 파일 인덱스 증가
        self.file_index += 1

    def read_points(self, cloud, field_names=None, skip_nans=False, uvs=[]):
        """ PointCloud2 메시지를 numpy 배열로 변환 """
        assert isinstance(cloud, PointCloud2), 'cloud is not a sensor_msgs.msg.PointCloud2'

        fmt = _get_struct_fmt(cloud.is_bigendian, cloud.fields, field_names)
        width, height, point_step, row_step, data = cloud.width, cloud.height, cloud.point_step, cloud.row_step, cloud.data
        unpack_from = struct.Struct(fmt).unpack_from

        if skip_nans:
            for v in range(height):
                offset = row_step * v
                for u in range(width):
                    p = unpack_from(data, offset)
                    if not any(map(isnan, p)):
                        yield p
                    offset += point_step
        else:
            for v in range(height):
                offset = row_step * v
                for u in range(width):
                    yield unpack_from(data, offset)
                    offset += point_step


def main(args=None):
    rclpy.init(args=args)
    pointcloud_saver = PointCloudSaver()
    rclpy.spin(pointcloud_saver)
    pointcloud_saver.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
