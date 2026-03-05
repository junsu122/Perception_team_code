// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from darknet_ros_msgs:msg/ObjectCount.idl
// generated code does not contain a copyright notice

#ifndef DARKNET_ROS_MSGS__MSG__DETAIL__OBJECT_COUNT__STRUCT_H_
#define DARKNET_ROS_MSGS__MSG__DETAIL__OBJECT_COUNT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/ObjectCount in the package darknet_ros_msgs.
typedef struct darknet_ros_msgs__msg__ObjectCount
{
  std_msgs__msg__Header header;
  int8_t count;
} darknet_ros_msgs__msg__ObjectCount;

// Struct for a sequence of darknet_ros_msgs__msg__ObjectCount.
typedef struct darknet_ros_msgs__msg__ObjectCount__Sequence
{
  darknet_ros_msgs__msg__ObjectCount * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} darknet_ros_msgs__msg__ObjectCount__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DARKNET_ROS_MSGS__MSG__DETAIL__OBJECT_COUNT__STRUCT_H_
