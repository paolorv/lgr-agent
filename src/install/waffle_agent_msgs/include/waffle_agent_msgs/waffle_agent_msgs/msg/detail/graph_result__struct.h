// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from waffle_agent_msgs:msg/GraphResult.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "waffle_agent_msgs/msg/graph_result.h"


#ifndef WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__STRUCT_H_
#define WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'label'
#include "rosidl_runtime_c/string.h"
// Member 'position'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/GraphResult in the package waffle_agent_msgs.
typedef struct waffle_agent_msgs__msg__GraphResult
{
  int32_t node_id;
  rosidl_runtime_c__String label;
  float score;
  rosidl_runtime_c__float__Sequence position;
} waffle_agent_msgs__msg__GraphResult;

// Struct for a sequence of waffle_agent_msgs__msg__GraphResult.
typedef struct waffle_agent_msgs__msg__GraphResult__Sequence
{
  waffle_agent_msgs__msg__GraphResult * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} waffle_agent_msgs__msg__GraphResult__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__STRUCT_H_
