// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from darknet_ros_msgs:msg/BoundingBoxes.idl
// generated code does not contain a copyright notice

#ifndef DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOXES__STRUCT_H_
#define DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOXES__STRUCT_H_

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
// Member 'image_header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'bounding_boxes'
#include "darknet_ros_msgs/msg/detail/bounding_box__struct.h"

/// Struct defined in msg/BoundingBoxes in the package darknet_ros_msgs.
typedef struct darknet_ros_msgs__msg__BoundingBoxes
{
  std_msgs__msg__Header header;
  std_msgs__msg__Header image_header;
  darknet_ros_msgs__msg__BoundingBox__Sequence bounding_boxes;
} darknet_ros_msgs__msg__BoundingBoxes;

// Struct for a sequence of darknet_ros_msgs__msg__BoundingBoxes.
typedef struct darknet_ros_msgs__msg__BoundingBoxes__Sequence
{
  darknet_ros_msgs__msg__BoundingBoxes * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} darknet_ros_msgs__msg__BoundingBoxes__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DARKNET_ROS_MSGS__MSG__DETAIL__BOUNDING_BOXES__STRUCT_H_
