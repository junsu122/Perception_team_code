// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from darknet_ros_msgs:msg/BoundingBox.idl
// generated code does not contain a copyright notice

#ifndef DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOX__BUILDER_HPP_
#define DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOX__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "darknet_ros_msgs/msg/detail/bounding_box__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace darknet_ros_msgs
{

namespace msg
{

namespace builder
{

class Init_BoundingBox_class_id
{
public:
  explicit Init_BoundingBox_class_id(::darknet_ros_msgs::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  ::darknet_ros_msgs::msg::BoundingBox class_id(::darknet_ros_msgs::msg::BoundingBox::_class_id_type arg)
  {
    msg_.class_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::darknet_ros_msgs::msg::BoundingBox msg_;
};

class Init_BoundingBox_id
{
public:
  explicit Init_BoundingBox_id(::darknet_ros_msgs::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_class_id id(::darknet_ros_msgs::msg::BoundingBox::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_BoundingBox_class_id(msg_);
  }

private:
  ::darknet_ros_msgs::msg::BoundingBox msg_;
};

class Init_BoundingBox_ymax
{
public:
  explicit Init_BoundingBox_ymax(::darknet_ros_msgs::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_id ymax(::darknet_ros_msgs::msg::BoundingBox::_ymax_type arg)
  {
    msg_.ymax = std::move(arg);
    return Init_BoundingBox_id(msg_);
  }

private:
  ::darknet_ros_msgs::msg::BoundingBox msg_;
};

class Init_BoundingBox_xmax
{
public:
  explicit Init_BoundingBox_xmax(::darknet_ros_msgs::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_ymax xmax(::darknet_ros_msgs::msg::BoundingBox::_xmax_type arg)
  {
    msg_.xmax = std::move(arg);
    return Init_BoundingBox_ymax(msg_);
  }

private:
  ::darknet_ros_msgs::msg::BoundingBox msg_;
};

class Init_BoundingBox_ymin
{
public:
  explicit Init_BoundingBox_ymin(::darknet_ros_msgs::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_xmax ymin(::darknet_ros_msgs::msg::BoundingBox::_ymin_type arg)
  {
    msg_.ymin = std::move(arg);
    return Init_BoundingBox_xmax(msg_);
  }

private:
  ::darknet_ros_msgs::msg::BoundingBox msg_;
};

class Init_BoundingBox_xmin
{
public:
  explicit Init_BoundingBox_xmin(::darknet_ros_msgs::msg::BoundingBox & msg)
  : msg_(msg)
  {}
  Init_BoundingBox_ymin xmin(::darknet_ros_msgs::msg::BoundingBox::_xmin_type arg)
  {
    msg_.xmin = std::move(arg);
    return Init_BoundingBox_ymin(msg_);
  }

private:
  ::darknet_ros_msgs::msg::BoundingBox msg_;
};

class Init_BoundingBox_probability
{
public:
  Init_BoundingBox_probability()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BoundingBox_xmin probability(::darknet_ros_msgs::msg::BoundingBox::_probability_type arg)
  {
    msg_.probability = std::move(arg);
    return Init_BoundingBox_xmin(msg_);
  }

private:
  ::darknet_ros_msgs::msg::BoundingBox msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::darknet_ros_msgs::msg::BoundingBox>()
{
  return darknet_ros_msgs::msg::builder::Init_BoundingBox_probability();
}

}  // namespace darknet_ros_msgs

#endif  // DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOX__BUILDER_HPP_
