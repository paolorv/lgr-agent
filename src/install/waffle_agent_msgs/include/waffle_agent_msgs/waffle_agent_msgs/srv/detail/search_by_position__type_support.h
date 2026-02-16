// generated from rosidl_generator_c/resource/idl__type_support.h.em
// with input from waffle_agent_msgs:srv/SearchByPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "waffle_agent_msgs/srv/search_by_position.h"


#ifndef WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__TYPE_SUPPORT_H_
#define WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__TYPE_SUPPORT_H_

#include "rosidl_typesupport_interface/macros.h"

#include "waffle_agent_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_waffle_agent_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  waffle_agent_msgs,
  srv,
  SearchByPosition_Request
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_waffle_agent_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  waffle_agent_msgs,
  srv,
  SearchByPosition_Response
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_waffle_agent_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  waffle_agent_msgs,
  srv,
  SearchByPosition_Event
)(void);

#include "rosidl_runtime_c/service_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_waffle_agent_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c,
  waffle_agent_msgs,
  srv,
  SearchByPosition
)(void);

// Forward declare the function to create a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_waffle_agent_msgs
void *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  waffle_agent_msgs,
  srv,
  SearchByPosition
)(
  const rosidl_service_introspection_info_t * info,
  rcutils_allocator_t * allocator,
  const void * request_message,
  const void * response_message);

// Forward declare the function to destroy a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_waffle_agent_msgs
bool
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  waffle_agent_msgs,
  srv,
  SearchByPosition
)(
  void * event_msg,
  rcutils_allocator_t * allocator);

#ifdef __cplusplus
}
#endif

#endif  // WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__TYPE_SUPPORT_H_
