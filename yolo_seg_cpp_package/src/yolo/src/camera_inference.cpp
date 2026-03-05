#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include "seg/YOLO8Seg.hpp"

// 커스텀 메시지 include
#include "yolo_msg/msg/bounding_box.hpp"
#include "yolo_msg/msg/bounding_box_array.hpp"
#include <chrono>  // 추가

using Detection = Segmentation;

const std::map<std::string, cv::Scalar> class_color_map = {
    {"yellow", cv::Scalar(0, 255, 255)},
    {"blue",   cv::Scalar(255, 0, 0)}
};

void draw_colored_boxes(cv::Mat& frame,
                        const std::vector<Detection>& detections,
                        const std::vector<std::string>& class_names)
{
    for (const auto& det : detections) {
        std::string class_name = class_names[det.classId];
        cv::Scalar color = cv::Scalar(0, 255, 0);
        auto it = class_color_map.find(class_name);
        if (it != class_color_map.end()) color = it->second;

        cv::rectangle(frame,
                      cv::Point(det.box.x, det.box.y),
                      cv::Point(det.box.x + det.box.width, det.box.y + det.box.height),
                      color, 2);

        std::string label = class_name;
        int baseLine = 0;
        cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        int top = std::max(det.box.y, labelSize.height);
        cv::rectangle(frame,
                      cv::Point(det.box.x, top - labelSize.height),
                      cv::Point(det.box.x + labelSize.width, top + baseLine),
                      color, cv::FILLED);
        cv::putText(frame, label, cv::Point(det.box.x, top),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0), 1);
    }
}

void publish_and_draw_object_means(const std::vector<Detection>& detections,
                                   const std::vector<std::string>& class_names,
                                   const std::string& target_class,
                                   rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr pub,
                                   rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr pixel_pub,
                                   const std::string& frame_id,
                                   cv::Mat& frame,
                                   const cv::Scalar& color)
{
    for (const auto& det : detections) {
        if (class_names[det.classId] == target_class && !det.mask.empty()) {
            double sum_x = 0.0, sum_y = 0.0;
            int count = 0;
            for (int y = 0; y < det.mask.rows; ++y) {
                for (int x = 0; x < det.mask.cols; ++x) {
                    if (det.mask.at<uint8_t>(y, x) > 0) {
                        sum_x += x;
                        sum_y += y;
                        count++;
                    }
                }
            }
            if (count > 0) {
                geometry_msgs::msg::PointStamped pt;
                pt.header.stamp = rclcpp::Clock().now();
                pt.header.frame_id = frame_id;
                pt.point.x = sum_x / count;
                pt.point.y = sum_y / count;
                pt.point.z = 0.0;
                pub->publish(pt);

                int draw_x = static_cast<int>(pt.point.x);
                int draw_y = static_cast<int>(pt.point.y);
                cv::circle(frame, cv::Point(draw_x, draw_y), 8, color, -1);

                pixel_pub->publish(pt);
            }
        }
    }
}

class YoloImageNode : public rclcpp::Node
{
public:
    YoloImageNode()
        : Node("yolo_image_node"),
          detector("/home/junsu/1.yolo_seg_linux/src/yolo/models/best.onnx", "/home/junsu/1.yolo_seg_linux/src/yolo/models/label.names", false)
    {
        using std::placeholders::_1;
        sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "camera2/image_raw", 10,
            std::bind(&YoloImageNode::image_callback, this, _1));

        yellow_pub_ = this->create_publisher<geometry_msgs::msg::PointStamped>("yellow_cone", 10);
        blue_pub_   = this->create_publisher<geometry_msgs::msg::PointStamped>("blue_cone", 10);
        pixel_circle_pub_ = this->create_publisher<geometry_msgs::msg::PointStamped>("pixel_circle", 10);
        bounding_box_pub_ = this->create_publisher<yolo_msg::msg::BoundingBoxArray>("bounding_box", 10);

        cv::namedWindow("Detections");
    }

    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        } catch (cv_bridge::Exception& e) {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }
        cv::Mat frame = cv_ptr->image;

        auto t1 = std::chrono::high_resolution_clock::now();
        std::vector<Detection> detections = detector.segment(frame);
        auto t2 = std::chrono::high_resolution_clock::now();

        double inference_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();
        RCLCPP_INFO(this->get_logger(), "YOLOv8 ONNX Inference Time: %.2f ms", inference_ms);
        
        // 바운딩 박스 메시지 생성 및 publish
        yolo_msg::msg::BoundingBoxArray bbox_msg;
        bbox_msg.header.stamp = this->now();
        bbox_msg.header.frame_id = "camera_map";
        for (const auto& det : detections) {
            yolo_msg::msg::BoundingBox box;
            box.x = det.box.x;
            box.y = det.box.y;
            box.width = det.box.width;
            box.height = det.box.height;
            box.class_name = detector.getClassNames()[det.classId];
            box.confidence = det.conf;
            bbox_msg.boxes.push_back(box);
        }
        bounding_box_pub_->publish(bbox_msg);

        draw_colored_boxes(frame, detections, detector.getClassNames());

        publish_and_draw_object_means(detections, detector.getClassNames(), "yellow", yellow_pub_, pixel_circle_pub_, "camera_link", frame, class_color_map.at("yellow"));
        publish_and_draw_object_means(detections, detector.getClassNames(), "blue", blue_pub_, pixel_circle_pub_, "camera_link", frame, class_color_map.at("blue"));

        cv::imshow("Detections", frame);
        if (cv::waitKey(1) == 'q') {
            rclcpp::shutdown();
        }
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
    rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr yellow_pub_;
    rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr blue_pub_;
    rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr pixel_circle_pub_;
    rclcpp::Publisher<yolo_msg::msg::BoundingBoxArray>::SharedPtr bounding_box_pub_;
    YOLOv8SegDetector detector;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<YoloImageNode>();
    rclcpp::spin(node);
    cv::destroyAllWindows();
    return 0;
}
