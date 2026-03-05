// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from yolo_msg:msg/BoundingBoxArray.idl
// generated code does not contain a copyright notice

#ifndef YOLO_MSG__MSG__DETAIL__BOUNDING_BOX_ARRAY__STRUCT_H_
#define YOLO_MSG__MSG__DETAIL__BOUNDING_BOX_ARRAY__STRUCT_H_

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
// Member 'boxes'
#include "yolo_msg/msg/detail/bounding_box__struct.h"

/// Struct defined in msg/BoundingBoxArray in the package yolo_msg.
typedef struct yolo_msg__msg__BoundingBoxArray
{
  std_msgs__msg__Header header;
  yolo_msg__msg__BoundingBox__Sequence boxes;
} yolo_msg__msg__BoundingBoxArray;

// Struct for a sequence of yolo_msg__msg__BoundingBoxArray.
typedef struct yolo_msg__msg__BoundingBoxArray__Sequence
{
  yolo_msg__msg__BoundingBoxArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} yolo_msg__msg__BoundingBoxArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // YOLO_MSG__MSG__DETAIL__BOUNDING_BOX_ARRAY__STRUCT_H_
