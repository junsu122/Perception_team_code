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
import re

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

def get_next_file_index(folder_path):
    """폴더 내에서 가장 큰 번호를 찾아 그 다음 번호를 반환"""
    max_index = 0
    pattern = re.compile(r"(\d+)\.pcd$")
    if not os.path.exists(folder_path):
        os.makedirs(folder_path)
    for fname in os.listdir(folder_path):
        match = pattern.match(fname)
        if match:
            idx = int(match.group(1))
            if idx > max_index:
                max_index = idx
    return max_index + 1

class PointCloudSaver(Node):
    def __init__(self):
        super().__init__('pointcloud_saver')
        self.folder_path = "/home/junsu/1.cam/src/fusion/fusion/file1"
        self.file_index = get_next_file_index(self.folder_path)
        self.latest_cloud = None
        self.latest_image = None
        self.bridge = CvBridge()
        self.saved = False

        self.subscription_pc = self.create_subscription(
            PointCloud2,
            '/cropbox_filtered',
            self.pointcloud_callback,
            10)

        self.subscription_img = self.create_subscription(
            Image,
            '/camera3/image_raw',
            self.image_callback,
            10)

    def pointcloud_callback(self, msg):
        self.latest_cloud = msg
        self.try_save_and_exit()

    def image_callback(self, msg):
        self.latest_image = msg
        self.try_save_and_exit()

    def try_save_and_exit(self):
        if self.latest_cloud is not None and self.latest_image is not None and not self.saved:
            self.saved = True
            self.save_data(self.latest_cloud, self.latest_image)
            self.get_logger().info("저장 완료. 노드를 종료합니다.")
            rclpy.shutdown()

    def save_data(self, cloud_msg, img_msg):
        filename_base = os.path.join(self.folder_path, f"{self.file_index}")
        filename_pcd = filename_base + ".pcd"
        filename_img = filename_base + ".jpg"

        # PointCloud 저장
        points = np.array(list(self.read_points(cloud_msg, field_names=("x", "y", "z"), skip_nans=True)))
        cloud = o3d.geometry.PointCloud()
        cloud.points = o3d.utility.Vector3dVector(points)
        o3d.io.write_point_cloud(filename_pcd, cloud)

        # Image 저장
        image = self.bridge.imgmsg_to_cv2(img_msg, "bgr8")
        cv2.imwrite(filename_img, image)

        self.get_logger().info(f"[SAVED] PointCloud: {filename_pcd}")
        self.get_logger().info(f"[SAVED] Image: {filename_img}")

        self.file_index += 1

    def read_points(self, cloud, field_names=None, skip_nans=False, uvs=[]):
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
