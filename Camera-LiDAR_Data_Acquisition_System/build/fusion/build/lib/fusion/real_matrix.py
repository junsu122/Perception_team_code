import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2, PointField
from sensor_msgs_py.point_cloud2 import create_cloud
import numpy as np

class FusionTest(Node):
    def __init__(self):
        super().__init__('fusion_test')
        self.lidar_subscription = self.create_subscription(
            PointCloud2,
            '/cropbox_filtered',
            self.lidar_callback,
            10
        )

        self.coord_pub = self.create_publisher(PointCloud2, 'transformed_points', 10)

        self.RTlc = np.array([[0.322600756408528, -0.946535104218665, -2.201054451071716, 0.2470],
                              [-0.219947705552146, -0.074737018741928, -0.972644531600273, -0.1655],
                              [0.920625743061203, 0.313824273298497, -0.232298443175321, -0.2163],
                              ])

        # Camera matrix should be a square matrix for inverse calculation
        self.Mc = np.array([[505.7409238317752, 0, 323.6391281673634],
                            [0, 506.2566945016900, 268.6714435674729],
                            [0, 0, 1]])

    def lidar_callback(self, msg):
        # Multiple 2D points (u, v, 1)
        camera_points_list = [
            [171,251,1],
            [384,301,1],
            [161,219,1],
            [399,215,1],
            [260,432,1]
        ]

        transformed_points = []
        for camera_points in camera_points_list:
            # Convert to NumPy array and calculate real world coordinates
            camera_points_np = np.array(camera_points)
            
            # Use pseudo-inverse if RTlc is not square
            RTlc_pinv = np.linalg.pinv(self.RTlc)
            Mc_pinv = np.linalg.pinv(self.Mc)
            
            res = np.dot(RTlc_pinv, np.dot(Mc_pinv, camera_points_np.T))

            # Transformed camera points (3D points)
            real_x = res[0]/res[3]
            real_y = res[1]/res[3]
            real_z = res[2]/res[3]
            transformed_points.append([real_x, real_y, real_z])

        # Publish PointCloud2 message
        header = msg.header
        fields = [
            PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
            PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
            PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1)
        ]

        # Create PointCloud2 message
        transformed_points_msg = create_cloud(header, fields, transformed_points)

        # Publish transformed points
        self.coord_pub.publish(transformed_points_msg)

def main(args=None):
    rclpy.init(args=args)
    node = FusionTest()

    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

if __name__ == '__main__':
    main()
