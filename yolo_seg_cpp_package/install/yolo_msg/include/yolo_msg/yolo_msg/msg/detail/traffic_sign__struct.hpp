// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from yolo_msg:msg/TrafficSign.idl
// generated code does not contain a copyright notice

#ifndef YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__STRUCT_HPP_
#define YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__yolo_msg__msg__TrafficSign __attribute__((deprecated))
#else
# define DEPRECATED__yolo_msg__msg__TrafficSign __declspec(deprecated)
#endif

namespace yolo_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TrafficSign_
{
  using Type = TrafficSign_<ContainerAllocator>;

  explicit TrafficSign_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->class_id = 0l;
    }
  }

  explicit TrafficSign_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->class_id = 0l;
    }
  }

  // field types and members
  using _pose_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _pose_type pose;
  using _class_id_type =
    int32_t;
  _class_id_type class_id;

  // setters for named parameter idiom
  Type & set__pose(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__class_id(
    const int32_t & _arg)
  {
    this->class_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    yolo_msg::msg::TrafficSign_<ContainerAllocator> *;
  using ConstRawPtr =
    const yolo_msg::msg::TrafficSign_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<yolo_msg::msg::TrafficSign_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<yolo_msg::msg::TrafficSign_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      yolo_msg::msg::TrafficSign_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<yolo_msg::msg::TrafficSign_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      yolo_msg::msg::TrafficSign_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<yolo_msg::msg::TrafficSign_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<yolo_msg::msg::TrafficSign_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<yolo_msg::msg::TrafficSign_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__yolo_msg__msg__TrafficSign
    std::shared_ptr<yolo_msg::msg::TrafficSign_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__yolo_msg__msg__TrafficSign
    std::shared_ptr<yolo_msg::msg::TrafficSign_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TrafficSign_ & other) const
  {
    if (this->pose != other.pose) {
      return false;
    }
    if (this->class_id != other.class_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const TrafficSign_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TrafficSign_

// alias to use template instance with default allocator
using TrafficSign =
  yolo_msg::msg::TrafficSign_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace yolo_msg

#endif  // YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__STRUCT_HPP_
