// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from yolo_msg:msg/TrafficSign.idl
// generated code does not contain a copyright notice
#include "yolo_msg/msg/detail/traffic_sign__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `pose`
#include "geometry_msgs/msg/detail/pose__functions.h"

bool
yolo_msg__msg__TrafficSign__init(yolo_msg__msg__TrafficSign * msg)
{
  if (!msg) {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__init(&msg->pose)) {
    yolo_msg__msg__TrafficSign__fini(msg);
    return false;
  }
  // class_id
  return true;
}

void
yolo_msg__msg__TrafficSign__fini(yolo_msg__msg__TrafficSign * msg)
{
  if (!msg) {
    return;
  }
  // pose
  geometry_msgs__msg__Pose__fini(&msg->pose);
  // class_id
}

bool
yolo_msg__msg__TrafficSign__are_equal(const yolo_msg__msg__TrafficSign * lhs, const yolo_msg__msg__TrafficSign * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  // class_id
  if (lhs->class_id != rhs->class_id) {
    return false;
  }
  return true;
}

bool
yolo_msg__msg__TrafficSign__copy(
  const yolo_msg__msg__TrafficSign * input,
  yolo_msg__msg__TrafficSign * output)
{
  if (!input || !output) {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  // class_id
  output->class_id = input->class_id;
  return true;
}

yolo_msg__msg__TrafficSign *
yolo_msg__msg__TrafficSign__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  yolo_msg__msg__TrafficSign * msg = (yolo_msg__msg__TrafficSign *)allocator.allocate(sizeof(yolo_msg__msg__TrafficSign), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(yolo_msg__msg__TrafficSign));
  bool success = yolo_msg__msg__TrafficSign__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
yolo_msg__msg__TrafficSign__destroy(yolo_msg__msg__TrafficSign * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    yolo_msg__msg__TrafficSign__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
yolo_msg__msg__TrafficSign__Sequence__init(yolo_msg__msg__TrafficSign__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  yolo_msg__msg__TrafficSign * data = NULL;

  if (size) {
    data = (yolo_msg__msg__TrafficSign *)allocator.zero_allocate(size, sizeof(yolo_msg__msg__TrafficSign), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = yolo_msg__msg__TrafficSign__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        yolo_msg__msg__TrafficSign__fini(&data[i - 1]);
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
yolo_msg__msg__TrafficSign__Sequence__fini(yolo_msg__msg__TrafficSign__Sequence * array)
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
      yolo_msg__msg__TrafficSign__fini(&array->data[i]);
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

yolo_msg__msg__TrafficSign__Sequence *
yolo_msg__msg__TrafficSign__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  yolo_msg__msg__TrafficSign__Sequence * array = (yolo_msg__msg__TrafficSign__Sequence *)allocator.allocate(sizeof(yolo_msg__msg__TrafficSign__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = yolo_msg__msg__TrafficSign__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
yolo_msg__msg__TrafficSign__Sequence__destroy(yolo_msg__msg__TrafficSign__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    yolo_msg__msg__TrafficSign__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
yolo_msg__msg__TrafficSign__Sequence__are_equal(const yolo_msg__msg__TrafficSign__Sequence * lhs, const yolo_msg__msg__TrafficSign__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!yolo_msg__msg__TrafficSign__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
yolo_msg__msg__TrafficSign__Sequence__copy(
  const yolo_msg__msg__TrafficSign__Sequence * input,
  yolo_msg__msg__TrafficSign__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(yolo_msg__msg__TrafficSign);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    yolo_msg__msg__TrafficSign * data =
      (yolo_msg__msg__TrafficSign *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!yolo_msg__msg__TrafficSign__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          yolo_msg__msg__TrafficSign__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!yolo_msg__msg__TrafficSign__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
