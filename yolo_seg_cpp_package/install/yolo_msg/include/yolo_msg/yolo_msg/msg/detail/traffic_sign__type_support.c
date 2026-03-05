// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from yolo_msg:msg/TrafficSign.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "yolo_msg/msg/detail/traffic_sign__rosidl_typesupport_introspection_c.h"
#include "yolo_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "yolo_msg/msg/detail/traffic_sign__functions.h"
#include "yolo_msg/msg/detail/traffic_sign__struct.h"


// Include directives for member types
// Member `pose`
#include "geometry_msgs/msg/pose.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  yolo_msg__msg__TrafficSign__init(message_memory);
}

void yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_fini_function(void * message_memory)
{
  yolo_msg__msg__TrafficSign__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_message_member_array[2] = {
  {
    "pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(yolo_msg__msg__TrafficSign, pose),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "class_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(yolo_msg__msg__TrafficSign, class_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_message_members = {
  "yolo_msg__msg",  // message namespace
  "TrafficSign",  // message name
  2,  // number of fields
  sizeof(yolo_msg__msg__TrafficSign),
  yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_message_member_array,  // message members
  yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_init_function,  // function to initialize message memory (memory has to be allocated)
  yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_message_type_support_handle = {
  0,
  &yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_yolo_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, yolo_msg, msg, TrafficSign)() {
  yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Pose)();
  if (!yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_message_type_support_handle.typesupport_identifier) {
    yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &yolo_msg__msg__TrafficSign__rosidl_typesupport_introspection_c__TrafficSign_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
