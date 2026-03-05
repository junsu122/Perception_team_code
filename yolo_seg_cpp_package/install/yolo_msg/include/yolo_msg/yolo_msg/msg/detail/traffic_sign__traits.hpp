// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from yolo_msg:msg/TrafficSign.idl
// generated code does not contain a copyright notice

#ifndef YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__TRAITS_HPP_
#define YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "yolo_msg/msg/detail/traffic_sign__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace yolo_msg
{

namespace msg
{

inline void to_flow_style_yaml(
  const TrafficSign & msg,
  std::ostream & out)
{
  out << "{";
  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
    out << ", ";
  }

  // member: class_id
  {
    out << "class_id: ";
    rosidl_generator_traits::value_to_yaml(msg.class_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TrafficSign & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }

  // member: class_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "class_id: ";
    rosidl_generator_traits::value_to_yaml(msg.class_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TrafficSign & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace yolo_msg

namespace rosidl_generator_traits
{

[[deprecated("use yolo_msg::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const yolo_msg::msg::TrafficSign & msg,
  std::ostream & out, size_t indentation = 0)
{
  yolo_msg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use yolo_msg::msg::to_yaml() instead")]]
inline std::string to_yaml(const yolo_msg::msg::TrafficSign & msg)
{
  return yolo_msg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<yolo_msg::msg::TrafficSign>()
{
  return "yolo_msg::msg::TrafficSign";
}

template<>
inline const char * name<yolo_msg::msg::TrafficSign>()
{
  return "yolo_msg/msg/TrafficSign";
}

template<>
struct has_fixed_size<yolo_msg::msg::TrafficSign>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Pose>::value> {};

template<>
struct has_bounded_size<yolo_msg::msg::TrafficSign>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Pose>::value> {};

template<>
struct is_message<yolo_msg::msg::TrafficSign>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__TRAITS_HPP_
