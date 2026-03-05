// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from yolo_msg:msg/TrafficSign.idl
// generated code does not contain a copyright notice

#ifndef YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__BUILDER_HPP_
#define YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "yolo_msg/msg/detail/traffic_sign__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace yolo_msg
{

namespace msg
{

namespace builder
{

class Init_TrafficSign_class_id
{
public:
  explicit Init_TrafficSign_class_id(::yolo_msg::msg::TrafficSign & msg)
  : msg_(msg)
  {}
  ::yolo_msg::msg::TrafficSign class_id(::yolo_msg::msg::TrafficSign::_class_id_type arg)
  {
    msg_.class_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::yolo_msg::msg::TrafficSign msg_;
};

class Init_TrafficSign_pose
{
public:
  Init_TrafficSign_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TrafficSign_class_id pose(::yolo_msg::msg::TrafficSign::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_TrafficSign_class_id(msg_);
  }

private:
  ::yolo_msg::msg::TrafficSign msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::yolo_msg::msg::TrafficSign>()
{
  return yolo_msg::msg::builder::Init_TrafficSign_pose();
}

}  // namespace yolo_msg

#endif  // YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__BUILDER_HPP_
