// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from yolo_msg:msg/BoundingBox.idl
// generated code does not contain a copyright notice

#ifndef YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__BUILDER_HPP_
#define YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "yolo_msg/msg/detail/bounding_box__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace yolo_msg
{

namespace msg
{

namespace builder
{

class Init_BoundingBox_pixel_center_y
{
public:
  explicit Init_BoundingBox_pixel_center_y(::yolo_msg::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  ::yolo_msg::msg::BoundingBox pixel_center_y(::yolo_msg::msg::BoundingBox::_pixel_center_y_type arg)
  {
    msg_.pixel_center_y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBox msg_;
};

class Init_BoundingBox_pixel_center_x
{
public:
  explicit Init_BoundingBox_pixel_center_x(::yolo_msg::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_pixel_center_y pixel_center_x(::yolo_msg::msg::BoundingBox::_pixel_center_x_type arg)
  {
    msg_.pixel_center_x = std::move(arg);
    return Init_BoundingBox_pixel_center_y(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBox msg_;
};

class Init_BoundingBox_center_y
{
public:
  explicit Init_BoundingBox_center_y(::yolo_msg::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_pixel_center_x center_y(::yolo_msg::msg::BoundingBox::_center_y_type arg)
  {
    msg_.center_y = std::move(arg);
    return Init_BoundingBox_pixel_center_x(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBox msg_;
};

class Init_BoundingBox_center_x
{
public:
  explicit Init_BoundingBox_center_x(::yolo_msg::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_center_y center_x(::yolo_msg::msg::BoundingBox::_center_x_type arg)
  {
    msg_.center_x = std::move(arg);
    return Init_BoundingBox_center_y(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBox msg_;
};

class Init_BoundingBox_confidence
{
public:
  explicit Init_BoundingBox_confidence(::yolo_msg::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_center_x confidence(::yolo_msg::msg::BoundingBox::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return Init_BoundingBox_center_x(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBox msg_;
};

class Init_BoundingBox_class_name
{
public:
  explicit Init_BoundingBox_class_name(::yolo_msg::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_confidence class_name(::yolo_msg::msg::BoundingBox::_class_name_type arg)
  {
    msg_.class_name = std::move(arg);
    return Init_BoundingBox_confidence(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBox msg_;
};

class Init_BoundingBox_height
{
public:
  explicit Init_BoundingBox_height(::yolo_msg::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_class_name height(::yolo_msg::msg::BoundingBox::_height_type arg)
  {
    msg_.height = std::move(arg);
    return Init_BoundingBox_class_name(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBox msg_;
};

class Init_BoundingBox_width
{
public:
  explicit Init_BoundingBox_width(::yolo_msg::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_height width(::yolo_msg::msg::BoundingBox::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_BoundingBox_height(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBox msg_;
};

class Init_BoundingBox_y
{
public:
  explicit Init_BoundingBox_y(::yolo_msg::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_width y(::yolo_msg::msg::BoundingBox::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_BoundingBox_width(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBox msg_;
};

class Init_BoundingBox_x
{
public:
  Init_BoundingBox_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BoundingBox_y x(::yolo_msg::msg::BoundingBox::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_BoundingBox_y(msg_);
  }

private:
  ::yolo_msg::msg::BoundingBox msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::yolo_msg::msg::BoundingBox>()
{
  return yolo_msg::msg::builder::Init_BoundingBox_x();
}

}  // namespace yolo_msg

#endif  // YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__BUILDER_HPP_
