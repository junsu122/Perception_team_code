#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_array.hpp"
#include "geometry_msgs/msg/point_stamped.hpp"
#include "yolo_msg/msg/bounding_box_array.hpp"
#include "yolo_msg/msg/traffic_sign.hpp"

#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <unordered_map>

class TrafficSignChecker : public rclcpp::Node
{
public:
    TrafficSignChecker()
    : Node("traffic_sign_checker")
    {
        pose_sub_ = create_subscription<geometry_msgs::msg::PoseArray>(
            "/traffic_poses", 10,
            std::bind(&TrafficSignChecker::poseCallback, this, std::placeholders::_1));

        bbox_sub_ = create_subscription<yolo_msg::msg::BoundingBoxArray>(
            "/yolo/detections", 10,
            std::bind(&TrafficSignChecker::bboxCallback, this, std::placeholders::_1));

        traffic_pub_ = create_publisher<yolo_msg::msg::TrafficSign>("/traffic_sign", 10);

        traffic_rviz_pub_ = create_publisher<geometry_msgs::msg::PointStamped>("/traffic_sign_rviz", 10);

        // 카메라 내부 파라미터 (3x4) 
        C_Mc_ << 0, 0, 0, 0,            // put your parameter
                 0, 0, 0, 0,  
                 0, 0, 0, 0;  

        // LiDAR → Camera 외부 파라미터 (4x4)
        C_RTlc_ << 0, 0, 0, 0,
                   0, 0, 0, 0,
                   0, 0, 0, 0,
                   0, 0, 0, 0;

        RCLCPP_INFO(this->get_logger(), "TrafficSignChecker node initialized.");
    }

private:
    void bboxCallback(const yolo_msg::msg::BoundingBoxArray::SharedPtr msg)
    {
        if (msg->boxes.empty()) {
            RCLCPP_WARN(get_logger(), "Received BoundingBoxArray but it's empty.");
        } else {
            RCLCPP_INFO(get_logger(), "Received %lu bounding boxes.", msg->boxes.size());
        }

        last_bboxes_ = msg->boxes;
        has_bbox_ = !last_bboxes_.empty();
    }

    int getClassID(const std::string& class_name) {
        static const std::unordered_map<std::string, int> class_map = {
            {"A1", 1}, {"A2", 2}, {"A3", 3},
            {"B1", 4}, {"B2", 5}, {"B3", 6}
        };
        auto it = class_map.find(class_name);
        return (it != class_map.end()) ? it->second : -1;
    }

    void poseCallback(const geometry_msgs::msg::PoseArray::SharedPtr msg)
    {
        if (!has_bbox_) {
            RCLCPP_WARN(get_logger(), "No bounding boxes received yet.");
            return;
        }

        for (const auto& pose : msg->poses)
        {
            Eigen::Vector4d point_lidar;
            point_lidar << pose.position.x, pose.position.y, pose.position.z, 1.0;

            Eigen::Matrix<double, 3, 4> P = C_Mc_ * C_RTlc_;
            Eigen::Vector3d pixel_homo = P * point_lidar;

            double u = pixel_homo(0) / pixel_homo(2);
            double v = pixel_homo(1) / pixel_homo(2) ;

            for (const auto& bbox : last_bboxes_)
            {
                int x = bbox.x, y = bbox.y, w = bbox.width, h = bbox.height;

                if (u >= x && u <= x + w && v >= y && v <= y + h)
                {
                    int class_id = getClassID(bbox.class_name);

                    yolo_msg::msg::TrafficSign traffic_msg;
                    traffic_msg.pose = pose;
                    traffic_msg.class_id = class_id;
                    traffic_pub_->publish(traffic_msg);

                    geometry_msgs::msg::PointStamped rviz_point;
                    rviz_point.header.stamp = get_clock()->now();
                    rviz_point.header.frame_id = "velodyne";  // 실제 LiDAR 프레임 확인 필요
                    rviz_point.point = pose.position;
                    traffic_rviz_pub_->publish(rviz_point);

                    RCLCPP_INFO(get_logger(),
                        "3D point (%.1f, %.1f) matched with bbox [%s] (id: %d)",
                        u, v, bbox.class_name.c_str(), class_id);

                    break;  // 한 개만 매칭하면 종료
                }
            }
        }
    }

    rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr pose_sub_;
    rclcpp::Subscription<yolo_msg::msg::BoundingBoxArray>::SharedPtr bbox_sub_;
    rclcpp::Publisher<yolo_msg::msg::TrafficSign>::SharedPtr traffic_pub_;
    rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr traffic_rviz_pub_;

    Eigen::Matrix<double, 3, 4> C_Mc_;
    Eigen::Matrix<double, 4, 4> C_RTlc_;

    std::vector<yolo_msg::msg::BoundingBox> last_bboxes_;
    bool has_bbox_ = false;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TrafficSignChecker>());
    rclcpp::shutdown();
    return 0;
}
