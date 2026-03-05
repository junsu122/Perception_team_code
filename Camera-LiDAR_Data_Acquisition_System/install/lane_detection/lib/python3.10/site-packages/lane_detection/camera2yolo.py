import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
from ultralytics import YOLO
import cv2

class YoloNode(Node):
    def __init__(self):
        super().__init__('yolo_node')
        # 구독할 토픽 이름 (camera1/image_raw)
        self.subscription = self.create_subscription(
            Image,
            'camera1/image_raw',  # ← 본인 토픽명에 맞게 수정
            self.listener_callback,
            10
        )
        # 결과 publish할 토픽
        self.publisher = self.create_publisher(
            Image,
            'yolo/image_detected',
            10
        )
        self.bridge = CvBridge()
        # 학습된 모델 경로로 수정
        self.model = YOLO('/home/junsu/Yolo cone tracking test/yolo/yolov8/runs/detect/train/weights/last.pt')

    def listener_callback(self, msg):
        # ROS2 Image → OpenCV 이미지
        frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        # YOLO 추론
        results = self.model(frame)
        # 결과 이미지 얻기
        annotated_frame = results[0].plot()
        # 결과 publish (OpenCV → ROS2 Image)
        detected_msg = self.bridge.cv2_to_imgmsg(annotated_frame, encoding='bgr8')
        detected_msg.header = msg.header  # 타임스탬프 등 복사
        self.publisher.publish(detected_msg)
        # 로컬에서 결과를 바로 보고 싶으면 아래 줄 활성화
        cv2.imshow("YOLO Detection", annotated_frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            cv2.destroyAllWindows()
            rclpy.shutdown()

def main(args=None):
    rclpy.init(args=args)
    node = YoloNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    cv2.destroyAllWindows()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
