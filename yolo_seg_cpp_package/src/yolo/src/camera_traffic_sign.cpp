/**
 * @file camera_inference_node.cpp
 * @brief ROS2 node for real-time object detection using YOLO models with image topic input
 */

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

#include "tools/BoundedThreadSafeQueue.hpp"

// YOLO 모델 중 하나만 활성화
#include "det/YOLO8.hpp"  // 또는 YOLO5.hpp, YOLO7.hpp 등

// 커스텀 메시지
#include "yolo_msg/msg/bounding_box.hpp"
#include "yolo_msg/msg/bounding_box_array.hpp"
#include <chrono>  // 추가


struct FrameData {
    cv::Mat resized_image;
    cv::Size original_size;
    cv::Mat original_image;  // 후처리 및 디스플레이용 원본 이미지
};

class CameraInferenceNode : public rclcpp::Node
{
public:
    CameraInferenceNode()
        : Node("camera_inference_node"), stopFlag(false)
    {
        // 설정값
        const std::string modelPath = "/home/junsu/1.yolo_seg_linux/src/yolo/src/models/1.onnx";
        const std::string labelsPath = "/home/junsu/1.yolo_seg_linux/src/yolo/src/models/traffic_sign.names";
        const bool isGPU = true;

        // YOLO 초기화
        detector = std::make_shared<YOLO8Detector>(modelPath, labelsPath, isGPU);

        // 이미지 토픽 구독
        image_sub = image_transport::create_subscription(
            this, "/camera1/image_raw",
            std::bind(&CameraInferenceNode::imageCallback, this, std::placeholders::_1),
            "raw"
        );

        // 결과 퍼블리셔 초기화
        bbox_pub = this->create_publisher<yolo_msg::msg::BoundingBoxArray>("/yolo/bounding_boxes", 10);

        // 스레드 시작
        consumerThread = std::thread([this]() { consumerLoop(); });
        displayThread = std::thread([this]() { displayLoop(); });

        RCLCPP_INFO(this->get_logger(), "Camera inference node started.");
    }

    ~CameraInferenceNode()
    {
        stopFlag.store(true);
        frameQueue.set_finished();
        processedQueue.set_finished();
        if (consumerThread.joinable()) consumerThread.join();
        if (displayThread.joinable()) displayThread.join();
        cv::destroyAllWindows();
    }

private:
    std::shared_ptr<YOLO8Detector> detector;

    image_transport::Subscriber image_sub;
    rclcpp::Publisher<yolo_msg::msg::BoundingBoxArray>::SharedPtr bbox_pub;

    BoundedThreadSafeQueue<FrameData> frameQueue{2};
    BoundedThreadSafeQueue<std::pair<cv::Mat, std::vector<Detection>>> processedQueue{2};

    std::atomic<bool> stopFlag;
    std::thread consumerThread;
    std::thread displayThread;

    void imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr &msg)
    {
        try {
            cv::Mat original_frame = cv_bridge::toCvShare(msg, "bgr8")->image;
            FrameData data;
            data.original_size = original_frame.size();
            data.original_image = original_frame.clone();

            // 모델 입력 크기인 640x640로 리사이즈
            cv::resize(original_frame, data.resized_image, cv::Size(640, 640));

            if (!frameQueue.enqueue(data)) {
                RCLCPP_WARN(this->get_logger(), "Frame queue full. Dropping frame.");
            }
        } catch (const cv_bridge::Exception &e) {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        }
    }

    void consumerLoop()
    {
        FrameData data;
        while (!stopFlag.load() && frameQueue.dequeue(data))
        {
            auto start = std::chrono::steady_clock::now();

            // 모델 추론
            std::vector<Detection> detections = detector->detect(data.resized_image);

            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            RCLCPP_INFO(this->get_logger(), "Inference time: %ld ms, Detections: %zu", elapsed_ms, detections.size());

            // 바운딩 박스 좌표를 원본 크기로 보정
            float scale_x = static_cast<float>(data.original_size.width) / 640.0f;
            float scale_y = static_cast<float>(data.original_size.height) / 640.0f;

            for (auto& det : detections)
            {
                det.box.x *= scale_x;
                det.box.y *= scale_y;
                det.box.width *= scale_x;
                det.box.height *= scale_y;
            }

            // BoundingBoxArray 메시지 생성 및 퍼블리시
            yolo_msg::msg::BoundingBoxArray bbox_array_msg;
            bbox_array_msg.header.stamp = now();
            bbox_array_msg.header.frame_id = "camera1";

            for (const auto& det : detections)
            {
                yolo_msg::msg::BoundingBox box;
                box.x = det.box.x;
                box.y = det.box.y;
                box.width = det.box.width;
                box.height = det.box.height;
                box.class_name = detector->getClassNames()[det.classId];
                box.confidence = det.conf;

                bbox_array_msg.boxes.push_back(box);
            }

            bbox_pub->publish(bbox_array_msg);

            // 디스플레이용 원본 이미지와 검출 결과 큐에 넣기
            if (!processedQueue.enqueue(std::make_pair(data.original_image, detections)))
                break;
        }
        processedQueue.set_finished();
    }

    void displayLoop()
    {
        std::pair<cv::Mat, std::vector<Detection>> item;
        while (!stopFlag.load() && processedQueue.dequeue(item))
        {
            cv::Mat displayFrame = item.first.clone(); // 원본 이미지 복사
            detector->drawBoundingBoxMask(displayFrame, item.second);

            cv::imshow("YOLO Detections", displayFrame);
            if (cv::waitKey(1) == 'q') {
                stopFlag.store(true);
                frameQueue.set_finished();
                processedQueue.set_finished();
                break;
            }
        }
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CameraInferenceNode>());
    rclcpp::shutdown();
    return 0;
}
