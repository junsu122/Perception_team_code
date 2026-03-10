#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <sensor_msgs/point_cloud_conversion.hpp>  // sensor_msgs 헤더로 수정
#include <visualization_msgs/msg/marker.hpp>
#include <geometry_msgs/msg/point.hpp>

class TunnelMapping : public rclcpp::Node
{
public:
    TunnelMapping() : Node("tunnel_mapping")
    {
        // Subscriber 설정
        subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/cropbox_filtered", 10, std::bind(&TunnelMapping::lidar_callback, this, std::placeholders::_1));

        // Marker 퍼블리셔 설정 (RViz에 표시)
        marker_pub_ = this->create_publisher<visualization_msgs::msg::Marker>("/visualization_marker", 10);
    }

private:
    void lidar_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

        // PointCloud2 메시지를 pcl::PointCloud로 변환
        // sensor_msgs::fromROSMsg(*msg, *cloud);  // sensor_msgs에서 제공하는 fromROSMsg 사용

        // LiDAR 데이터 처리 및 장애물 감지
        process_lidar_data(cloud);

        // Marker 메시지 생성
        visualization_msgs::msg::Marker marker;
        marker.header.frame_id = "tunnel";  // 'tunnel' 프레임으로 마커 설정
        marker.header.stamp = this->get_clock()->now();
        marker.ns = "tunnel_obstacles";
        marker.action = visualization_msgs::msg::Marker::ADD;
        marker.type = visualization_msgs::msg::Marker::SPHERE_LIST;
        marker.id = 0;
        marker.pose.orientation.w = 1.0;
        marker.scale.x = 0.1;
        marker.scale.y = 0.1;
        marker.scale.z = 0.1;  // 마커 크기 설정

        // 각 점에 대해 마커 색상 설정 및 주위의 z 값과 유사한 점 찾기
        double z_threshold = 0.2;  // 비슷한 z 값의 범위 설정
        for (size_t i = 0; i < cloud->points.size(); ++i)
        {
            bool similar_z = true;
            double current_z = cloud->points[i].z;

            // 주변 점들과 z 값이 비슷한지 확인
            for (size_t j = 0; j < cloud->points.size(); ++j)
            {
                if (i != j)
                {
                    double diff = std::abs(current_z - cloud->points[j].z);
                    if (diff > z_threshold)
                    {
                        similar_z = false;
                        break;
                    }
                }
            }

            // 비슷한 z 값인 경우 하얀색 마커로 추가
            if (similar_z)
            {
                geometry_msgs::msg::Point p;
                p.x = cloud->points[i].x;
                p.y = cloud->points[i].y;
                p.z = cloud->points[i].z;
                marker.points.push_back(p);

                // 마커 색상 설정 (하얀색)
                std_msgs::msg::ColorRGBA color;
                color.r = 1.0;
                color.g = 1.0;
                color.b = 1.0;
                color.a = 1.0;  // 불투명하게 하여 완전한 하얀색 표시
                marker.colors.push_back(color);
            }
        }

        // 마커 퍼블리시
        marker_pub_->publish(marker);
    }

    void process_lidar_data(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
    {
        // LiDAR 데이터를 처리하고 장애물을 탐지하는 로직을 구현합니다.
        for (const auto& point : cloud->points)
        {
            // 예시로 간단하게 z 값이 2m 이상인 점은 동적 장애물로 분류
            if (point.z > 2.0)
            {
                // 동적 장애물 처리
            }
            else
            {
                // 정적 장애물 처리
            }
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TunnelMapping>());
    rclcpp::shutdown();
    return 0;
}
