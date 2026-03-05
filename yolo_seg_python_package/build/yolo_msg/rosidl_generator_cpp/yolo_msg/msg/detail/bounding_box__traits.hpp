// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from yolo_msg:msg/BoundingBox.idl
// generated code does not contain a copyright notice

#ifndef YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__TRAITS_HPP_
#define YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "yolo_msg/msg/detail/bounding_box__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace yolo_msg
{

namespace msg
{

inline void to_flow_style_yaml(
  const BoundingBox & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: width
  {
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << ", ";
  }

  // member: height
  {
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << ", ";
  }

  // member: class_name
  {
    out << "class_name: ";
    rosidl_generator_traits::value_to_yaml(msg.class_name, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << ", ";
  }

  // member: center_x
  {
    out << "center_x: ";
    rosidl_generator_traits::value_to_yaml(msg.center_x, out);
    out << ", ";
  }

  // member: center_y
  {
    out << "center_y: ";
    rosidl_generator_traits::value_to_yaml(msg.center_y, out);
    out << ", ";
  }

  // member: pixel_center_x
  {
    out << "pixel_center_x: ";
    rosidl_generator_traits::value_to_yaml(msg.pixel_center_x, out);
    out << ", ";
  }

  // member: pixel_center_y
  {
    out << "pixel_center_y: ";
    rosidl_generator_traits::value_to_yaml(msg.pixel_center_y, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BoundingBox & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << "\n";
  }

  // member: height
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << "\n";
  }

  // member: class_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "class_name: ";
    rosidl_generator_traits::value_to_yaml(msg.class_name, out);
    out << "\n";
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }

  // member: center_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "center_x: ";
    rosidl_generator_traits::value_to_yaml(msg.center_x, out);
    out << "\n";
  }

  // member: center_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "center_y: ";
    rosidl_generator_traits::value_to_yaml(msg.center_y, out);
    out << "\n";
  }

  // member: pixel_center_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pixel_center_x: ";
    rosidl_generator_traits::value_to_yaml(msg.pixel_center_x, out);
    out << "\n";
  }

  // member: pixel_center_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pixel_center_y: ";
    rosidl_generator_traits::value_to_yaml(msg.pixel_center_y, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BoundingBox & msg, bool use_flow_style = false)
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
  const yolo_msg::msg::BoundingBox & msg,
  std::ostream & out, size_t indentation = 0)
{
  yolo_msg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use yolo_msg::msg::to_yaml() instead")]]
inline std::string to_yaml(const yolo_msg::msg::BoundingBox & msg)
{
  return yolo_msg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<yolo_msg::msg::BoundingBox>()
{
  return "yolo_msg::msg::BoundingBox";
}

template<>
inline const char * name<yolo_msg::msg::BoundingBox>()
{
  return "yolo_msg/msg/BoundingBox";
}

template<>
struct has_fixed_size<yolo_msg::msg::BoundingBox>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<yolo_msg::msg::BoundingBox>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<yolo_msg::msg::BoundingBox>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__TRAITS_HPP_
