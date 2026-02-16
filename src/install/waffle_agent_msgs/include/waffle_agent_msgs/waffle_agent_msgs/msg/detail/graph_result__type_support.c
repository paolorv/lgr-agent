// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from waffle_agent_msgs:msg/GraphResult.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "waffle_agent_msgs/msg/detail/graph_result__rosidl_typesupport_introspection_c.h"
#include "waffle_agent_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "waffle_agent_msgs/msg/detail/graph_result__functions.h"
#include "waffle_agent_msgs/msg/detail/graph_result__struct.h"


// Include directives for member types
// Member `label`
#include "rosidl_runtime_c/string_functions.h"
// Member `position`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  waffle_agent_msgs__msg__GraphResult__init(message_memory);
}

void waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_fini_function(void * message_memory)
{
  waffle_agent_msgs__msg__GraphResult__fini(message_memory);
}

size_t waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__size_function__GraphResult__position(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__get_const_function__GraphResult__position(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__get_function__GraphResult__position(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__fetch_function__GraphResult__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__get_const_function__GraphResult__position(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__assign_function__GraphResult__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__get_function__GraphResult__position(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__resize_function__GraphResult__position(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_message_member_array[4] = {
  {
    "node_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(waffle_agent_msgs__msg__GraphResult, node_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "label",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(waffle_agent_msgs__msg__GraphResult, label),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "score",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(waffle_agent_msgs__msg__GraphResult, score),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(waffle_agent_msgs__msg__GraphResult, position),  // bytes offset in struct
    NULL,  // default value
    waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__size_function__GraphResult__position,  // size() function pointer
    waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__get_const_function__GraphResult__position,  // get_const(index) function pointer
    waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__get_function__GraphResult__position,  // get(index) function pointer
    waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__fetch_function__GraphResult__position,  // fetch(index, &value) function pointer
    waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__assign_function__GraphResult__position,  // assign(index, value) function pointer
    waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__resize_function__GraphResult__position  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_message_members = {
  "waffle_agent_msgs__msg",  // message namespace
  "GraphResult",  // message name
  4,  // number of fields
  sizeof(waffle_agent_msgs__msg__GraphResult),
  false,  // has_any_key_member_
  waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_message_member_array,  // message members
  waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_init_function,  // function to initialize message memory (memory has to be allocated)
  waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_message_type_support_handle = {
  0,
  &waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_message_members,
  get_message_typesupport_handle_function,
  &waffle_agent_msgs__msg__GraphResult__get_type_hash,
  &waffle_agent_msgs__msg__GraphResult__get_type_description,
  &waffle_agent_msgs__msg__GraphResult__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_waffle_agent_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, msg, GraphResult)() {
  if (!waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_message_type_support_handle.typesupport_identifier) {
    waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &waffle_agent_msgs__msg__GraphResult__rosidl_typesupport_introspection_c__GraphResult_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
