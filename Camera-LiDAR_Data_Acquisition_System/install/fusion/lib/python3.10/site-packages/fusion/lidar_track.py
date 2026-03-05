import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2
import ros2_numpy  # sensor_msgs.point_cloud2 대체
import numpy as np
import open3d as o3d
from sklearn.cluster import DBSCAN
from pykalman import KalmanFilter

class LiDARObjectTracker(Node):
    def __init__(self):
        super().__init__('lidar_object_tracker')
        self.subscription = self.create_subscription(PointCloud2, '/cropbox_filtered', self.pointcloud_callback, 10)
        
        # Kalman 필터 설정 (x, y 위치와 속도 추적)
        self.kf = KalmanFilter(
            transition_matrices=np.array([[1, 0, 1, 0],
                                          [0, 1, 0, 1],
                                          [0, 0, 1, 0],
                                          [0, 0, 0, 1]]),
            observation_matrices=np.array([[1, 0, 0, 0],
                                           [0, 1, 0, 0]])
        )
        self.state = np.array([0, 0, 0, 0])
        self.covariance = np.eye(4)
        
        self.prev_clusters = {}
        self.tracked_objects = {}

    def pointcloud_callback(self, msg):
        """LiDAR 포인트 클라우드 처리 및 객체 추적"""
        try:
            pc_array = ros2_numpy.numpify(msg)  # sensor_msgs 모듈 대체
            points = np.vstack((pc_array['x'], pc_array['y'], pc_array['z'])).T
            points = points[~np.isnan(points).any(axis=1)]

            if len(points) == 0:
                self.get_logger().warn("빈 포인트 클라우드 수신")
                return
            
            # DBSCAN 클러스터링
            clustering = DBSCAN(eps=0.5, min_samples=5).fit(points[:, :2])
            labels = clustering.labels_
            unique_labels = set(labels)

            clusters = {}
            for label in unique_labels:
                if label == -1:
                    continue  # Noise 제거
                cluster_points = points[labels == label]
                center = np.mean(cluster_points, axis=0)[:2]
                clusters[label] = center

            # 객체 추적 (Kalman Filter)
            for label, center in clusters.items():
                if label not in self.tracked_objects:
                    self.tracked_objects[label] = self.state
                self.state, self.covariance = self.kf.filter_update(
                    self.tracked_objects[label],
                    self.covariance,
                    observation=np.array([center[0], center[1]])
                )
                self.tracked_objects[label] = self.state

            # 시각화
            self.visualize_objects(clusters)

        except Exception as e:
            self.get_logger().error(f"포인트 클라우드 처리 중 오류 발생: {e}")

    def visualize_objects(self, clusters):
        """객체 위치 시각화"""
        if not clusters:
            self.get_logger().warn("시각화할 클러스터가 없습니다.")
            return

        point_cloud = o3d.geometry.PointCloud()
        points = []
        colors = []
        for label, center in clusters.items():
            points.append([center[0], center[1], 0])
            colors.append([1, 0, 0])  # 빨간색으로 객체 표시

        if points:
            point_cloud.points = o3d.utility.Vector3dVector(np.array(points))
            point_cloud.colors = o3d.utility.Vector3dVector(np.array(colors))
            o3d.visualization.draw_geometries([point_cloud])

def main(args=None):
    rclpy.init(args=args)
    node = LiDARObjectTracker()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
