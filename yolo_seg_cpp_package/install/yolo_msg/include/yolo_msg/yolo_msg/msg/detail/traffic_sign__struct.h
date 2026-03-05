// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from yolo_msg:msg/TrafficSign.idl
// generated code does not contain a copyright notice

#ifndef YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__STRUCT_H_
#define YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in msg/TrafficSign in the package yolo_msg.
typedef struct yolo_msg__msg__TrafficSign
{
  geometry_msgs__msg__Pose pose;
  int32_t class_id;
} yolo_msg__msg__TrafficSign;

// Struct for a sequence of yolo_msg__msg__TrafficSign.
typedef struct yolo_msg__msg__TrafficSign__Sequence
{
  yolo_msg__msg__TrafficSign * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} yolo_msg__msg__TrafficSign__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // YOLO_MSG__MSG__DETAIL__TRAFFIC_SIGN__STRUCT_H_
