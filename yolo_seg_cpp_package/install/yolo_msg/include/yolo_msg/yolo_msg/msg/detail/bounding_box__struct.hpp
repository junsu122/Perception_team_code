// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from yolo_msg:msg/BoundingBox.idl
// generated code does not contain a copyright notice

#ifndef YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__STRUCT_HPP_
#define YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__yolo_msg__msg__BoundingBox __attribute__((deprecated))
#else
# define DEPRECATED__yolo_msg__msg__BoundingBox __declspec(deprecated)
#endif

namespace yolo_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BoundingBox_
{
  using Type = BoundingBox_<ContainerAllocator>;

  explicit BoundingBox_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0l;
      this->y = 0l;
      this->width = 0l;
      this->height = 0l;
      this->class_name = "";
      this->confidence = 0.0f;
      this->center_x = 0.0f;
      this->center_y = 0.0f;
      this->pixel_center_x = 0.0;
      this->pixel_center_y = 0.0;
    }
  }

  explicit BoundingBox_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : class_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0l;
      this->y = 0l;
      this->width = 0l;
      this->height = 0l;
      this->class_name = "";
      this->confidence = 0.0f;
      this->center_x = 0.0f;
      this->center_y = 0.0f;
      this->pixel_center_x = 0.0;
      this->pixel_center_y = 0.0;
    }
  }

  // field types and members
  using _x_type =
    int32_t;
  _x_type x;
  using _y_type =
    int32_t;
  _y_type y;
  using _width_type =
    int32_t;
  _width_type width;
  using _height_type =
    int32_t;
  _height_type height;
  using _class_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _class_name_type class_name;
  using _confidence_type =
    float;
  _confidence_type confidence;
  using _center_x_type =
    float;
  _center_x_type center_x;
  using _center_y_type =
    float;
  _center_y_type center_y;
  using _pixel_center_x_type =
    double;
  _pixel_center_x_type pixel_center_x;
  using _pixel_center_y_type =
    double;
  _pixel_center_y_type pixel_center_y;

  // setters for named parameter idiom
  Type & set__x(
    const int32_t & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const int32_t & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__width(
    const int32_t & _arg)
  {
    this->width = _arg;
    return *this;
  }
  Type & set__height(
    const int32_t & _arg)
  {
    this->height = _arg;
    return *this;
  }
  Type & set__class_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->class_name = _arg;
    return *this;
  }
  Type & set__confidence(
    const float & _arg)
  {
    this->confidence = _arg;
    return *this;
  }
  Type & set__center_x(
    const float & _arg)
  {
    this->center_x = _arg;
    return *this;
  }
  Type & set__center_y(
    const float & _arg)
  {
    this->center_y = _arg;
    return *this;
  }
  Type & set__pixel_center_x(
    const double & _arg)
  {
    this->pixel_center_x = _arg;
    return *this;
  }
  Type & set__pixel_center_y(
    const double & _arg)
  {
    this->pixel_center_y = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    yolo_msg::msg::BoundingBox_<ContainerAllocator> *;
  using ConstRawPtr =
    const yolo_msg::msg::BoundingBox_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<yolo_msg::msg::BoundingBox_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<yolo_msg::msg::BoundingBox_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      yolo_msg::msg::BoundingBox_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<yolo_msg::msg::BoundingBox_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      yolo_msg::msg::BoundingBox_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<yolo_msg::msg::BoundingBox_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<yolo_msg::msg::BoundingBox_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<yolo_msg::msg::BoundingBox_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__yolo_msg__msg__BoundingBox
    std::shared_ptr<yolo_msg::msg::BoundingBox_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__yolo_msg__msg__BoundingBox
    std::shared_ptr<yolo_msg::msg::BoundingBox_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BoundingBox_ & other) const
  {
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->width != other.width) {
      return false;
    }
    if (this->height != other.height) {
      return false;
    }
    if (this->class_name != other.class_name) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    if (this->center_x != other.center_x) {
      return false;
    }
    if (this->center_y != other.center_y) {
      return false;
    }
    if (this->pixel_center_x != other.pixel_center_x) {
      return false;
    }
    if (this->pixel_center_y != other.pixel_center_y) {
      return false;
    }
    return true;
  }
  bool operator!=(const BoundingBox_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BoundingBox_

// alias to use template instance with default allocator
using BoundingBox =
  yolo_msg::msg::BoundingBox_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace yolo_msg

#endif  // YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__STRUCT_HPP_
