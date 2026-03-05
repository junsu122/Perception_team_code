// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from darknet_ros_msgs:msg/BoundingBox.idl
// generated code does not contain a copyright notice

#ifndef DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOX__STRUCT_H_
#define DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOX__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'class_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/BoundingBox in the package darknet_ros_msgs.
typedef struct darknet_ros_msgs__msg__BoundingBox
{
  double probability;
  int64_t xmin;
  int64_t ymin;
  int64_t xmax;
  int64_t ymax;
  int16_t id;
  rosidl_runtime_c__String class_id;
} darknet_ros_msgs__msg__BoundingBox;

// Struct for a sequence of darknet_ros_msgs__msg__BoundingBox.
typedef struct darknet_ros_msgs__msg__BoundingBox__Sequence
{
  darknet_ros_msgs__msg__BoundingBox * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} darknet_ros_msgs__msg__BoundingBox__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOX__STRUCT_H_
