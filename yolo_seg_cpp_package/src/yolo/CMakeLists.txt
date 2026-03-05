cmake_minimum_required(VERSION 3.10)
project(yolo)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)
find_package(yolo_msg REQUIRED)

set(ONNXRUNTIME_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/onnxruntime")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${ONNXRUNTIME_ROOT}/include
  ${OpenCV_INCLUDE_DIRS}
)

link_directories(${ONNXRUNTIME_ROOT}/lib)

add_executable(camera_inference src/camera_inference.cpp)
add_executable(traffic_sign_inference src/camera_traffic_sign.cpp)


# OpenCV_LIBRARIES 변수 사용 권장
target_link_libraries(camera_inference ${OpenCV_LIBRARIES} onnxruntime)
target_link_libraries(traffic_sign_inference ${OpenCV_LIBRARIES} onnxruntime)



ament_target_dependencies(camera_inference
  rclcpp sensor_msgs cv_bridge image_transport yolo_msg
)
ament_target_dependencies(traffic_sign_inference
  rclcpp sensor_msgs cv_bridge image_transport yolo_msg
)


target_include_directories(camera_inference PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(traffic_sign_inference PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)



install(TARGETS
  camera_inference
  traffic_sign_inference

  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
