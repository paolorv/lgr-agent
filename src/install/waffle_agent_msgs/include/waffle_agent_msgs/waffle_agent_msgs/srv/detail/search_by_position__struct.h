// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from waffle_agent_msgs:srv/SearchByPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "waffle_agent_msgs/srv/search_by_position.h"


#ifndef WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__STRUCT_H_
#define WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'query_position'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/SearchByPosition in the package waffle_agent_msgs.
typedef struct waffle_agent_msgs__srv__SearchByPosition_Request
{
  rosidl_runtime_c__float__Sequence query_position;
} waffle_agent_msgs__srv__SearchByPosition_Request;

// Struct for a sequence of waffle_agent_msgs__srv__SearchByPosition_Request.
typedef struct waffle_agent_msgs__srv__SearchByPosition_Request__Sequence
{
  waffle_agent_msgs__srv__SearchByPosition_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} waffle_agent_msgs__srv__SearchByPosition_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'top_k_results'
#include "waffle_agent_msgs/msg/detail/graph_result__struct.h"

/// Struct defined in srv/SearchByPosition in the package waffle_agent_msgs.
typedef struct waffle_agent_msgs__srv__SearchByPosition_Response
{
  waffle_agent_msgs__msg__GraphResult__Sequence top_k_results;
} waffle_agent_msgs__srv__SearchByPosition_Response;

// Struct for a sequence of waffle_agent_msgs__srv__SearchByPosition_Response.
typedef struct waffle_agent_msgs__srv__SearchByPosition_Response__Sequence
{
  waffle_agent_msgs__srv__SearchByPosition_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} waffle_agent_msgs__srv__SearchByPosition_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  waffle_agent_msgs__srv__SearchByPosition_Event__request__MAX_SIZE = 1
};
// response
enum
{
  waffle_agent_msgs__srv__SearchByPosition_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/SearchByPosition in the package waffle_agent_msgs.
typedef struct waffle_agent_msgs__srv__SearchByPosition_Event
{
  service_msgs__msg__ServiceEventInfo info;
  waffle_agent_msgs__srv__SearchByPosition_Request__Sequence request;
  waffle_agent_msgs__srv__SearchByPosition_Response__Sequence response;
} waffle_agent_msgs__srv__SearchByPosition_Event;

// Struct for a sequence of waffle_agent_msgs__srv__SearchByPosition_Event.
typedef struct waffle_agent_msgs__srv__SearchByPosition_Event__Sequence
{
  waffle_agent_msgs__srv__SearchByPosition_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} waffle_agent_msgs__srv__SearchByPosition_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__STRUCT_H_
