cmake_minimum_required(VERSION 3.10)
project(yolo_ort)

# ONNXRUNTIME_DIR을 직접 지정
set(ONNXRUNTIME_DIR "/home/junsu/1.yolo_seg/onnxruntime-linux-x64-1.20.1")

# ROS2 및 기타 패키지 찾기
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)


# include 디렉토리 추가
include_directories("include")
include_directories("${ONNXRUNTIME_DIR}/include")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 실행 파일 추가
add_executable(image_inference src/image_inference.cpp)
add_executable(camera_inference src/camera_inference.cpp)
add_executable(video_inference src/video_inference.cpp)

# 빌드 타겟별 include 디렉토리(명확성)
target_include_directories(image_inference PRIVATE "${ONNXRUNTIME_DIR}/include")
target_include_directories(camera_inference PRIVATE "${ONNXRUNTIME_DIR}/include")
target_include_directories(video_inference PRIVATE "${ONNXRUNTIME_DIR}/include")

# OpenCV 라이브러리 링크
target_link_libraries(image_inference ${OpenCV_LIBS})
target_link_libraries(camera_inference ${OpenCV_LIBS})
target_link_libraries(video_inference ${OpenCV_LIBS})

# ONNX Runtime 라이브러리 링크 (Linux 기준)
target_link_libraries(image_inference "${ONNXRUNTIME_DIR}/lib/libonnxruntime.so")
target_link_libraries(camera_inference "${ONNXRUNTIME_DIR}/lib/libonnxruntime.so")
target_link_libraries(video_inference "${ONNXRUNTIME_DIR}/lib/libonnxruntime.so")

# ROS2 의존성 연결
ament_target_dependencies(image_inference rclcpp sensor_msgs cv_bridge)
ament_target_dependencies(camera_inference rclcpp sensor_msgs cv_bridge)
ament_target_dependencies(video_inference rclcpp sensor_msgs cv_bridge)

# 설치 규칙 (필요 시)
install(TARGETS
  image_inference
  camera_inference
  video_inference
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
