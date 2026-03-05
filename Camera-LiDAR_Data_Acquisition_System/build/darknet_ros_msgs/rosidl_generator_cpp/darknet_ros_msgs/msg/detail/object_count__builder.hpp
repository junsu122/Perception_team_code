// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from darknet_ros_msgs:msg/ObjectCount.idl
// generated code does not contain a copyright notice

#ifndef DARKNET_ROS_MSGS__MSG__DETAIL__OBJECT_COUNT__BUILDER_HPP_
#define DARKNET_ROS_MSGS__MSG__DETAIL__OBJECT_COUNT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "darknet_ros_msgs/msg/detail/object_count__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace darknet_ros_msgs
{

namespace msg
{

namespace builder
{

class Init_ObjectCount_count
{
public:
  explicit Init_ObjectCount_count(::darknet_ros_msgs::msg::ObjectCount & msg)
  : msg_(msg)
  {}
  ::darknet_ros_msgs::msg::ObjectCount count(::darknet_ros_msgs::msg::ObjectCount::_count_type arg)
  {
    msg_.count = std::move(arg);
    return std::move(msg_);
  }

private:
  ::darknet_ros_msgs::msg::ObjectCount msg_;
};

class Init_ObjectCount_header
{
public:
  Init_ObjectCount_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ObjectCount_count header(::darknet_ros_msgs::msg::ObjectCount::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ObjectCount_count(msg_);
  }

private:
  ::darknet_ros_msgs::msg::ObjectCount msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::darknet_ros_msgs::msg::ObjectCount>()
{
  return darknet_ros_msgs::msg::builder::Init_ObjectCount_header();
}

}  // namespace darknet_ros_msgs

#endif  // DARKNET_ROS_MSGS__MSG__DETAIL__OBJECT_COUNT__BUILDER_HPP_
