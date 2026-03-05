import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import os

class ImageCaptureNode(Node):
    def __init__(self):
        super().__init__('image_capture_node')
        self.image_sub = self.create_subscription(Image, '/camera1/image_raw', self.image_callback, 10)
        self.bridge = CvBridge()

        # 저장 디렉토리 설정
        self.output_dir = "captured_images"
        os.makedirs(self.output_dir, exist_ok=True)

        # 파일 번호 추적
        existing_files = sorted(
            [int(f.split('.')[0]) for f in os.listdir(self.output_dir) if f.endswith('.jpg') and f.split('.')[0].isdigit()]
        )
        self.start_number = existing_files[-1] + 1 if existing_files else 1

        # 타이머 설정 (1초마다 캡처)
        self.timer = self.create_timer(1.0, self.capture_image)

        self.latest_image = None

    def image_callback(self, data):
        # 이미지를 업데이트
        self.latest_image = self.bridge.imgmsg_to_cv2(data, "bgr8")

    def capture_image(self):
        if self.latest_image is not None:
            # 파일 이름 생성
            image_filename = os.path.join(self.output_dir, f"{self.start_number}.jpg")

            # 이미지 저장
            cv2.imwrite(image_filename, self.latest_image)
            self.get_logger().info(f"Captured: {image_filename}")

            # 파일 번호 증가
            self.start_number += 1

def main(args=None):
    rclpy.init(args=args)
    image_capture_node = ImageCaptureNode()
    rclpy.spin(image_capture_node)
    image_capture_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

