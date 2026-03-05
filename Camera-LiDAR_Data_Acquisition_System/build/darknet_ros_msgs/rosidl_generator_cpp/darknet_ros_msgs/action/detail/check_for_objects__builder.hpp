// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from darknet_ros_msgs:action/CheckForObjects.idl
// generated code does not contain a copyright notice

#ifndef DARKNET_ROS_MSGS__ACTION__DETAIL__CHECK_FOR_OBJECTS__BUILDER_HPP_
#define DARKNET_ROS_MSGS__ACTION__DETAIL__CHECK_FOR_OBJECTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "darknet_ros_msgs/action/detail/check_for_objects__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace darknet_ros_msgs
{

namespace action
{

namespace builder
{

class Init_CheckForObjects_Goal_image
{
public:
  explicit Init_CheckForObjects_Goal_image(::darknet_ros_msgs::action::CheckForObjects_Goal & msg)
  : msg_(msg)
  {}
  ::darknet_ros_msgs::action::CheckForObjects_Goal image(::darknet_ros_msgs::action::CheckForObjects_Goal::_image_type arg)
  {
    msg_.image = std::move(arg);
    return std::move(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_Goal msg_;
};

class Init_CheckForObjects_Goal_id
{
public:
  Init_CheckForObjects_Goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CheckForObjects_Goal_image id(::darknet_ros_msgs::action::CheckForObjects_Goal::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_CheckForObjects_Goal_image(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::darknet_ros_msgs::action::CheckForObjects_Goal>()
{
  return darknet_ros_msgs::action::builder::Init_CheckForObjects_Goal_id();
}

}  // namespace darknet_ros_msgs


namespace darknet_ros_msgs
{

namespace action
{

namespace builder
{

class Init_CheckForObjects_Result_bounding_boxes
{
public:
  explicit Init_CheckForObjects_Result_bounding_boxes(::darknet_ros_msgs::action::CheckForObjects_Result & msg)
  : msg_(msg)
  {}
  ::darknet_ros_msgs::action::CheckForObjects_Result bounding_boxes(::darknet_ros_msgs::action::CheckForObjects_Result::_bounding_boxes_type arg)
  {
    msg_.bounding_boxes = std::move(arg);
    return std::move(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_Result msg_;
};

class Init_CheckForObjects_Result_id
{
public:
  Init_CheckForObjects_Result_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CheckForObjects_Result_bounding_boxes id(::darknet_ros_msgs::action::CheckForObjects_Result::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_CheckForObjects_Result_bounding_boxes(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::darknet_ros_msgs::action::CheckForObjects_Result>()
{
  return darknet_ros_msgs::action::builder::Init_CheckForObjects_Result_id();
}

}  // namespace darknet_ros_msgs


namespace darknet_ros_msgs
{

namespace action
{


}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::darknet_ros_msgs::action::CheckForObjects_Feedback>()
{
  return ::darknet_ros_msgs::action::CheckForObjects_Feedback(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace darknet_ros_msgs


namespace darknet_ros_msgs
{

namespace action
{

namespace builder
{

class Init_CheckForObjects_SendGoal_Request_goal
{
public:
  explicit Init_CheckForObjects_SendGoal_Request_goal(::darknet_ros_msgs::action::CheckForObjects_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::darknet_ros_msgs::action::CheckForObjects_SendGoal_Request goal(::darknet_ros_msgs::action::CheckForObjects_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_SendGoal_Request msg_;
};

class Init_CheckForObjects_SendGoal_Request_goal_id
{
public:
  Init_CheckForObjects_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CheckForObjects_SendGoal_Request_goal goal_id(::darknet_ros_msgs::action::CheckForObjects_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_CheckForObjects_SendGoal_Request_goal(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::darknet_ros_msgs::action::CheckForObjects_SendGoal_Request>()
{
  return darknet_ros_msgs::action::builder::Init_CheckForObjects_SendGoal_Request_goal_id();
}

}  // namespace darknet_ros_msgs


namespace darknet_ros_msgs
{

namespace action
{

namespace builder
{

class Init_CheckForObjects_SendGoal_Response_stamp
{
public:
  explicit Init_CheckForObjects_SendGoal_Response_stamp(::darknet_ros_msgs::action::CheckForObjects_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::darknet_ros_msgs::action::CheckForObjects_SendGoal_Response stamp(::darknet_ros_msgs::action::CheckForObjects_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_SendGoal_Response msg_;
};

class Init_CheckForObjects_SendGoal_Response_accepted
{
public:
  Init_CheckForObjects_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CheckForObjects_SendGoal_Response_stamp accepted(::darknet_ros_msgs::action::CheckForObjects_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_CheckForObjects_SendGoal_Response_stamp(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::darknet_ros_msgs::action::CheckForObjects_SendGoal_Response>()
{
  return darknet_ros_msgs::action::builder::Init_CheckForObjects_SendGoal_Response_accepted();
}

}  // namespace darknet_ros_msgs


namespace darknet_ros_msgs
{

namespace action
{

namespace builder
{

class Init_CheckForObjects_GetResult_Request_goal_id
{
public:
  Init_CheckForObjects_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::darknet_ros_msgs::action::CheckForObjects_GetResult_Request goal_id(::darknet_ros_msgs::action::CheckForObjects_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::darknet_ros_msgs::action::CheckForObjects_GetResult_Request>()
{
  return darknet_ros_msgs::action::builder::Init_CheckForObjects_GetResult_Request_goal_id();
}

}  // namespace darknet_ros_msgs


namespace darknet_ros_msgs
{

namespace action
{

namespace builder
{

class Init_CheckForObjects_GetResult_Response_result
{
public:
  explicit Init_CheckForObjects_GetResult_Response_result(::darknet_ros_msgs::action::CheckForObjects_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::darknet_ros_msgs::action::CheckForObjects_GetResult_Response result(::darknet_ros_msgs::action::CheckForObjects_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_GetResult_Response msg_;
};

class Init_CheckForObjects_GetResult_Response_status
{
public:
  Init_CheckForObjects_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CheckForObjects_GetResult_Response_result status(::darknet_ros_msgs::action::CheckForObjects_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_CheckForObjects_GetResult_Response_result(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::darknet_ros_msgs::action::CheckForObjects_GetResult_Response>()
{
  return darknet_ros_msgs::action::builder::Init_CheckForObjects_GetResult_Response_status();
}

}  // namespace darknet_ros_msgs


namespace darknet_ros_msgs
{

namespace action
{

namespace builder
{

class Init_CheckForObjects_FeedbackMessage_feedback
{
public:
  explicit Init_CheckForObjects_FeedbackMessage_feedback(::darknet_ros_msgs::action::CheckForObjects_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::darknet_ros_msgs::action::CheckForObjects_FeedbackMessage feedback(::darknet_ros_msgs::action::CheckForObjects_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_FeedbackMessage msg_;
};

class Init_CheckForObjects_FeedbackMessage_goal_id
{
public:
  Init_CheckForObjects_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CheckForObjects_FeedbackMessage_feedback goal_id(::darknet_ros_msgs::action::CheckForObjects_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_CheckForObjects_FeedbackMessage_feedback(msg_);
  }

private:
  ::darknet_ros_msgs::action::CheckForObjects_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::darknet_ros_msgs::action::CheckForObjects_FeedbackMessage>()
{
  return darknet_ros_msgs::action::builder::Init_CheckForObjects_FeedbackMessage_goal_id();
}

}  // namespace darknet_ros_msgs

#endif  // DARKNET_ROS_MSGS__ACTION__DETAIL__CHECK_FOR_OBJECTS__BUILDER_HPP_
