// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from yolo_msg:msg/BoundingBox.idl
// generated code does not contain a copyright notice

#ifndef YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__STRUCT_H_
#define YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'class_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/BoundingBox in the package yolo_msg.
typedef struct yolo_msg__msg__BoundingBox
{
  int32_t x;
  int32_t y;
  int32_t width;
  int32_t height;
  rosidl_runtime_c__String class_name;
  float confidence;
  /// 마스크 중심점 x좌표
  float center_x;
  /// 마스크 중심점 y좌표
  float center_y;
  /// 새 필드 추가
  double pixel_center_x;
  double pixel_center_y;
} yolo_msg__msg__BoundingBox;

// Struct for a sequence of yolo_msg__msg__BoundingBox.
typedef struct yolo_msg__msg__BoundingBox__Sequence
{
  yolo_msg__msg__BoundingBox * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} yolo_msg__msg__BoundingBox__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // YOLO_MSG__MSG__DETAIL__BOUNDING_BOX__STRUCT_H_
