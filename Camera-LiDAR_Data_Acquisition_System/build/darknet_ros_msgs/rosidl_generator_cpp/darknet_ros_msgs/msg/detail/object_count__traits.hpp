// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from darknet_ros_msgs:msg/ObjectCount.idl
// generated code does not contain a copyright notice

#ifndef DARKNET_ROS_MSGS__MSG__DETAIL__OBJECT_COUNT__TRAITS_HPP_
#define DARKNET_ROS_MSGS__MSG__DETAIL__OBJECT_COUNT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "darknet_ros_msgs/msg/detail/object_count__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace darknet_ros_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const ObjectCount & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: count
  {
    out << "count: ";
    rosidl_generator_traits::value_to_yaml(msg.count, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ObjectCount & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "count: ";
    rosidl_generator_traits::value_to_yaml(msg.count, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ObjectCount & msg, bool use_flow_style = false)
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

}  // namespace darknet_ros_msgs

namespace rosidl_generator_traits
{

[[deprecated("use darknet_ros_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const darknet_ros_msgs::msg::ObjectCount & msg,
  std::ostream & out, size_t indentation = 0)
{
  darknet_ros_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use darknet_ros_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const darknet_ros_msgs::msg::ObjectCount & msg)
{
  return darknet_ros_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<darknet_ros_msgs::msg::ObjectCount>()
{
  return "darknet_ros_msgs::msg::ObjectCount";
}

template<>
inline const char * name<darknet_ros_msgs::msg::ObjectCount>()
{
  return "darknet_ros_msgs/msg/ObjectCount";
}

template<>
struct has_fixed_size<darknet_ros_msgs::msg::ObjectCount>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<darknet_ros_msgs::msg::ObjectCount>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<darknet_ros_msgs::msg::ObjectCount>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DARKNET_ROS_MSGS__MSG__DETAIL__OBJECT_COUNT__TRAITS_HPP_
