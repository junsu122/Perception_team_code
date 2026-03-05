// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from yolo_msg:msg/BoundingBoxArray.idl
// generated code does not contain a copyright notice

#ifndef YOLO_MSG__MSG__DETAIL__BOUNDING_BOX_ARRAY__BUILDER_HPP_
#define YOLO_MSG__MSG__DETAIL__BOUNDING_BOX_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "yolo_msg/msg/detail/bounding_box_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace yolo_msg
{

namespace msg
{

namespace builder
{

class Init_BoundingBoxArray_boxes
{
public:
  explicit Init_BoundingBoxArray_boxes(::yolo_msg::msg::BoundingBoxArray & msg)
  : msg_(msg)
  {}
  ::yolo_msg::msg::BoundingBoxArray boxes(::yolo_msg::msg::BoundingBoxArray::_boxes_type arg)
  {
    msg_.boxes = std::move(arg);
    return std::move(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBoxArray msg_;
};

class Init_BoundingBoxArray_header
{
public:
  Init_BoundingBoxArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BoundingBoxArray_boxes header(::yolo_msg::msg::BoundingBoxArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_BoundingBoxArray_boxes(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBoxArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::yolo_msg::msg::BoundingBoxArray>()
{
  return yolo_msg::msg::builder::Init_BoundingBoxArray_header();
}

}  // namespace yolo_msg

#endif  // YOLO_MSG__MSG__DETAIL__BOUNDING_BOX_ARRAY__BUILDER_HPP_
