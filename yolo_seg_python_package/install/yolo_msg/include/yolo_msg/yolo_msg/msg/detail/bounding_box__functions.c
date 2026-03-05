// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from yolo_msg:msg/BoundingBox.idl
// generated code does not contain a copyright notice
#include "yolo_msg/msg/detail/bounding_box__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `class_name`
#include "rosidl_runtime_c/string_functions.h"

bool
yolo_msg__msg__BoundingBox__init(yolo_msg__msg__BoundingBox * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  // width
  // height
  // class_name
  if (!rosidl_runtime_c__String__init(&msg->class_name)) {
    yolo_msg__msg__BoundingBox__fini(msg);
    return false;
  }
  // confidence
  // center_x
  // center_y
  // pixel_center_x
  // pixel_center_y
  return true;
}

void
yolo_msg__msg__BoundingBox__fini(yolo_msg__msg__BoundingBox * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
  // width
  // height
  // class_name
  rosidl_runtime_c__String__fini(&msg->class_name);
  // confidence
  // center_x
  // center_y
  // pixel_center_x
  // pixel_center_y
}

bool
yolo_msg__msg__BoundingBox__are_equal(const yolo_msg__msg__BoundingBox * lhs, const yolo_msg__msg__BoundingBox * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  // class_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->class_name), &(rhs->class_name)))
  {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  // center_x
  if (lhs->center_x != rhs->center_x) {
    return false;
  }
  // center_y
  if (lhs->center_y != rhs->center_y) {
    return false;
  }
  // pixel_center_x
  if (lhs->pixel_center_x != rhs->pixel_center_x) {
    return false;
  }
  // pixel_center_y
  if (lhs->pixel_center_y != rhs->pixel_center_y) {
    return false;
  }
  return true;
}

bool
yolo_msg__msg__BoundingBox__copy(
  const yolo_msg__msg__BoundingBox * input,
  yolo_msg__msg__BoundingBox * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // width
  output->width = input->width;
  // height
  output->height = input->height;
  // class_name
  if (!rosidl_runtime_c__String__copy(
      &(input->class_name), &(output->class_name)))
  {
    return false;
  }
  // confidence
  output->confidence = input->confidence;
  // center_x
  output->center_x = input->center_x;
  // center_y
  output->center_y = input->center_y;
  // pixel_center_x
  output->pixel_center_x = input->pixel_center_x;
  // pixel_center_y
  output->pixel_center_y = input->pixel_center_y;
  return true;
}

yolo_msg__msg__BoundingBox *
yolo_msg__msg__BoundingBox__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  yolo_msg__msg__BoundingBox * msg = (yolo_msg__msg__BoundingBox *)allocator.allocate(sizeof(yolo_msg__msg__BoundingBox), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(yolo_msg__msg__BoundingBox));
  bool success = yolo_msg__msg__BoundingBox__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
yolo_msg__msg__BoundingBox__destroy(yolo_msg__msg__BoundingBox * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    yolo_msg__msg__BoundingBox__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
yolo_msg__msg__BoundingBox__Sequence__init(yolo_msg__msg__BoundingBox__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  yolo_msg__msg__BoundingBox * data = NULL;

  if (size) {
    data = (yolo_msg__msg__BoundingBox *)allocator.zero_allocate(size, sizeof(yolo_msg__msg__BoundingBox), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = yolo_msg__msg__BoundingBox__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        yolo_msg__msg__BoundingBox__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
yolo_msg__msg__BoundingBox__Sequence__fini(yolo_msg__msg__BoundingBox__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      yolo_msg__msg__BoundingBox__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

yolo_msg__msg__BoundingBox__Sequence *
yolo_msg__msg__BoundingBox__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  yolo_msg__msg__BoundingBox__Sequence * array = (yolo_msg__msg__BoundingBox__Sequence *)allocator.allocate(sizeof(yolo_msg__msg__BoundingBox__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = yolo_msg__msg__BoundingBox__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
yolo_msg__msg__BoundingBox__Sequence__destroy(yolo_msg__msg__BoundingBox__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    yolo_msg__msg__BoundingBox__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
yolo_msg__msg__BoundingBox__Sequence__are_equal(const yolo_msg__msg__BoundingBox__Sequence * lhs, const yolo_msg__msg__BoundingBox__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!yolo_msg__msg__BoundingBox__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
yolo_msg__msg__BoundingBox__Sequence__copy(
  const yolo_msg__msg__BoundingBox__Sequence * input,
  yolo_msg__msg__BoundingBox__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(yolo_msg__msg__BoundingBox);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    yolo_msg__msg__BoundingBox * data =
      (yolo_msg__msg__BoundingBox *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!yolo_msg__msg__BoundingBox__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          yolo_msg__msg__BoundingBox__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!yolo_msg__msg__BoundingBox__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
