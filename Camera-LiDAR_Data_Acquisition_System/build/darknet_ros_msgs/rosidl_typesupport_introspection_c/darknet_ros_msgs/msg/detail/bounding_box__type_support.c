// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from darknet_ros_msgs:msg/BoundingBox.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "darknet_ros_msgs/msg/detail/bounding_box__rosidl_typesupport_introspection_c.h"
#include "darknet_ros_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "darknet_ros_msgs/msg/detail/bounding_box__functions.h"
#include "darknet_ros_msgs/msg/detail/bounding_box__struct.h"


// Include directives for member types
// Member `class_id`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  darknet_ros_msgs__msg__BoundingBox__init(message_memory);
}

void darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_fini_function(void * message_memory)
{
  darknet_ros_msgs__msg__BoundingBox__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_message_member_array[7] = {
  {
    "probability",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(darknet_ros_msgs__msg__BoundingBox, probability),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "xmin",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(darknet_ros_msgs__msg__BoundingBox, xmin),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ymin",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(darknet_ros_msgs__msg__BoundingBox, ymin),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "xmax",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(darknet_ros_msgs__msg__BoundingBox, xmax),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ymax",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(darknet_ros_msgs__msg__BoundingBox, ymax),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(darknet_ros_msgs__msg__BoundingBox, id),  // bytes offset in struct
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
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(darknet_ros_msgs__msg__BoundingBox, class_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_message_members = {
  "darknet_ros_msgs__msg",  // message namespace
  "BoundingBox",  // message name
  7,  // number of fields
  sizeof(darknet_ros_msgs__msg__BoundingBox),
  darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_message_member_array,  // message members
  darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_init_function,  // function to initialize message memory (memory has to be allocated)
  darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_message_type_support_handle = {
  0,
  &darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_darknet_ros_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, darknet_ros_msgs, msg, BoundingBox)() {
  if (!darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_message_type_support_handle.typesupport_identifier) {
    darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &darknet_ros_msgs__msg__BoundingBox__rosidl_typesupport_introspection_c__BoundingBox_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
