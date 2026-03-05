// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from darknet_ros_msgs:msg/BoundingBoxes.idl
// generated code does not contain a copyright notice

#ifndef DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOXES__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOXES__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "darknet_ros_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "darknet_ros_msgs/msg/detail/bounding_boxes__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace darknet_ros_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_darknet_ros_msgs
cdr_serialize(
  const darknet_ros_msgs::msg::BoundingBoxes & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_darknet_ros_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  darknet_ros_msgs::msg::BoundingBoxes & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_darknet_ros_msgs
get_serialized_size(
  const darknet_ros_msgs::msg::BoundingBoxes & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_darknet_ros_msgs
max_serialized_size_BoundingBoxes(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace darknet_ros_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_darknet_ros_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, darknet_ros_msgs, msg, BoundingBoxes)();

#ifdef __cplusplus
}
#endif

#endif  // DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOXES__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
