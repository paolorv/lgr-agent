// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from waffle_agent_msgs:srv/SearchByLabel.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "waffle_agent_msgs/srv/detail/search_by_label__rosidl_typesupport_introspection_c.h"
#include "waffle_agent_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "waffle_agent_msgs/srv/detail/search_by_label__functions.h"
#include "waffle_agent_msgs/srv/detail/search_by_label__struct.h"


// Include directives for member types
// Member `query_text`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  waffle_agent_msgs__srv__SearchByLabel_Request__init(message_memory);
}

void waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_fini_function(void * message_memory)
{
  waffle_agent_msgs__srv__SearchByLabel_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_message_member_array[1] = {
  {
    "query_text",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(waffle_agent_msgs__srv__SearchByLabel_Request, query_text),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_message_members = {
  "waffle_agent_msgs__srv",  // message namespace
  "SearchByLabel_Request",  // message name
  1,  // number of fields
  sizeof(waffle_agent_msgs__srv__SearchByLabel_Request),
  false,  // has_any_key_member_
  waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_message_member_array,  // message members
  waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_message_type_support_handle = {
  0,
  &waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_message_members,
  get_message_typesupport_handle_function,
  &waffle_agent_msgs__srv__SearchByLabel_Request__get_type_hash,
  &waffle_agent_msgs__srv__SearchByLabel_Request__get_type_description,
  &waffle_agent_msgs__srv__SearchByLabel_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_waffle_agent_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel_Request)() {
  if (!waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_message_type_support_handle.typesupport_identifier) {
    waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__rosidl_typesupport_introspection_c.h"
// already included above
// #include "waffle_agent_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__functions.h"
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__struct.h"


// Include directives for member types
// Member `top_k_results`
#include "waffle_agent_msgs/msg/graph_result.h"
// Member `top_k_results`
#include "waffle_agent_msgs/msg/detail/graph_result__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  waffle_agent_msgs__srv__SearchByLabel_Response__init(message_memory);
}

void waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_fini_function(void * message_memory)
{
  waffle_agent_msgs__srv__SearchByLabel_Response__fini(message_memory);
}

size_t waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__size_function__SearchByLabel_Response__top_k_results(
  const void * untyped_member)
{
  const waffle_agent_msgs__msg__GraphResult__Sequence * member =
    (const waffle_agent_msgs__msg__GraphResult__Sequence *)(untyped_member);
  return member->size;
}

const void * waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__get_const_function__SearchByLabel_Response__top_k_results(
  const void * untyped_member, size_t index)
{
  const waffle_agent_msgs__msg__GraphResult__Sequence * member =
    (const waffle_agent_msgs__msg__GraphResult__Sequence *)(untyped_member);
  return &member->data[index];
}

void * waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__get_function__SearchByLabel_Response__top_k_results(
  void * untyped_member, size_t index)
{
  waffle_agent_msgs__msg__GraphResult__Sequence * member =
    (waffle_agent_msgs__msg__GraphResult__Sequence *)(untyped_member);
  return &member->data[index];
}

void waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__fetch_function__SearchByLabel_Response__top_k_results(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const waffle_agent_msgs__msg__GraphResult * item =
    ((const waffle_agent_msgs__msg__GraphResult *)
    waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__get_const_function__SearchByLabel_Response__top_k_results(untyped_member, index));
  waffle_agent_msgs__msg__GraphResult * value =
    (waffle_agent_msgs__msg__GraphResult *)(untyped_value);
  *value = *item;
}

void waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__assign_function__SearchByLabel_Response__top_k_results(
  void * untyped_member, size_t index, const void * untyped_value)
{
  waffle_agent_msgs__msg__GraphResult * item =
    ((waffle_agent_msgs__msg__GraphResult *)
    waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__get_function__SearchByLabel_Response__top_k_results(untyped_member, index));
  const waffle_agent_msgs__msg__GraphResult * value =
    (const waffle_agent_msgs__msg__GraphResult *)(untyped_value);
  *item = *value;
}

bool waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__resize_function__SearchByLabel_Response__top_k_results(
  void * untyped_member, size_t size)
{
  waffle_agent_msgs__msg__GraphResult__Sequence * member =
    (waffle_agent_msgs__msg__GraphResult__Sequence *)(untyped_member);
  waffle_agent_msgs__msg__GraphResult__Sequence__fini(member);
  return waffle_agent_msgs__msg__GraphResult__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_member_array[1] = {
  {
    "top_k_results",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(waffle_agent_msgs__srv__SearchByLabel_Response, top_k_results),  // bytes offset in struct
    NULL,  // default value
    waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__size_function__SearchByLabel_Response__top_k_results,  // size() function pointer
    waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__get_const_function__SearchByLabel_Response__top_k_results,  // get_const(index) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__get_function__SearchByLabel_Response__top_k_results,  // get(index) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__fetch_function__SearchByLabel_Response__top_k_results,  // fetch(index, &value) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__assign_function__SearchByLabel_Response__top_k_results,  // assign(index, value) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__resize_function__SearchByLabel_Response__top_k_results  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_members = {
  "waffle_agent_msgs__srv",  // message namespace
  "SearchByLabel_Response",  // message name
  1,  // number of fields
  sizeof(waffle_agent_msgs__srv__SearchByLabel_Response),
  false,  // has_any_key_member_
  waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_member_array,  // message members
  waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_type_support_handle = {
  0,
  &waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_members,
  get_message_typesupport_handle_function,
  &waffle_agent_msgs__srv__SearchByLabel_Response__get_type_hash,
  &waffle_agent_msgs__srv__SearchByLabel_Response__get_type_description,
  &waffle_agent_msgs__srv__SearchByLabel_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_waffle_agent_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel_Response)() {
  waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, msg, GraphResult)();
  if (!waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_type_support_handle.typesupport_identifier) {
    waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__rosidl_typesupport_introspection_c.h"
// already included above
// #include "waffle_agent_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__functions.h"
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "waffle_agent_msgs/srv/search_by_label.h"
// Member `request`
// Member `response`
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  waffle_agent_msgs__srv__SearchByLabel_Event__init(message_memory);
}

void waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_fini_function(void * message_memory)
{
  waffle_agent_msgs__srv__SearchByLabel_Event__fini(message_memory);
}

size_t waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__size_function__SearchByLabel_Event__request(
  const void * untyped_member)
{
  const waffle_agent_msgs__srv__SearchByLabel_Request__Sequence * member =
    (const waffle_agent_msgs__srv__SearchByLabel_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_const_function__SearchByLabel_Event__request(
  const void * untyped_member, size_t index)
{
  const waffle_agent_msgs__srv__SearchByLabel_Request__Sequence * member =
    (const waffle_agent_msgs__srv__SearchByLabel_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_function__SearchByLabel_Event__request(
  void * untyped_member, size_t index)
{
  waffle_agent_msgs__srv__SearchByLabel_Request__Sequence * member =
    (waffle_agent_msgs__srv__SearchByLabel_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__fetch_function__SearchByLabel_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const waffle_agent_msgs__srv__SearchByLabel_Request * item =
    ((const waffle_agent_msgs__srv__SearchByLabel_Request *)
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_const_function__SearchByLabel_Event__request(untyped_member, index));
  waffle_agent_msgs__srv__SearchByLabel_Request * value =
    (waffle_agent_msgs__srv__SearchByLabel_Request *)(untyped_value);
  *value = *item;
}

void waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__assign_function__SearchByLabel_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  waffle_agent_msgs__srv__SearchByLabel_Request * item =
    ((waffle_agent_msgs__srv__SearchByLabel_Request *)
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_function__SearchByLabel_Event__request(untyped_member, index));
  const waffle_agent_msgs__srv__SearchByLabel_Request * value =
    (const waffle_agent_msgs__srv__SearchByLabel_Request *)(untyped_value);
  *item = *value;
}

bool waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__resize_function__SearchByLabel_Event__request(
  void * untyped_member, size_t size)
{
  waffle_agent_msgs__srv__SearchByLabel_Request__Sequence * member =
    (waffle_agent_msgs__srv__SearchByLabel_Request__Sequence *)(untyped_member);
  waffle_agent_msgs__srv__SearchByLabel_Request__Sequence__fini(member);
  return waffle_agent_msgs__srv__SearchByLabel_Request__Sequence__init(member, size);
}

size_t waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__size_function__SearchByLabel_Event__response(
  const void * untyped_member)
{
  const waffle_agent_msgs__srv__SearchByLabel_Response__Sequence * member =
    (const waffle_agent_msgs__srv__SearchByLabel_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_const_function__SearchByLabel_Event__response(
  const void * untyped_member, size_t index)
{
  const waffle_agent_msgs__srv__SearchByLabel_Response__Sequence * member =
    (const waffle_agent_msgs__srv__SearchByLabel_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_function__SearchByLabel_Event__response(
  void * untyped_member, size_t index)
{
  waffle_agent_msgs__srv__SearchByLabel_Response__Sequence * member =
    (waffle_agent_msgs__srv__SearchByLabel_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__fetch_function__SearchByLabel_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const waffle_agent_msgs__srv__SearchByLabel_Response * item =
    ((const waffle_agent_msgs__srv__SearchByLabel_Response *)
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_const_function__SearchByLabel_Event__response(untyped_member, index));
  waffle_agent_msgs__srv__SearchByLabel_Response * value =
    (waffle_agent_msgs__srv__SearchByLabel_Response *)(untyped_value);
  *value = *item;
}

void waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__assign_function__SearchByLabel_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  waffle_agent_msgs__srv__SearchByLabel_Response * item =
    ((waffle_agent_msgs__srv__SearchByLabel_Response *)
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_function__SearchByLabel_Event__response(untyped_member, index));
  const waffle_agent_msgs__srv__SearchByLabel_Response * value =
    (const waffle_agent_msgs__srv__SearchByLabel_Response *)(untyped_value);
  *item = *value;
}

bool waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__resize_function__SearchByLabel_Event__response(
  void * untyped_member, size_t size)
{
  waffle_agent_msgs__srv__SearchByLabel_Response__Sequence * member =
    (waffle_agent_msgs__srv__SearchByLabel_Response__Sequence *)(untyped_member);
  waffle_agent_msgs__srv__SearchByLabel_Response__Sequence__fini(member);
  return waffle_agent_msgs__srv__SearchByLabel_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(waffle_agent_msgs__srv__SearchByLabel_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(waffle_agent_msgs__srv__SearchByLabel_Event, request),  // bytes offset in struct
    NULL,  // default value
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__size_function__SearchByLabel_Event__request,  // size() function pointer
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_const_function__SearchByLabel_Event__request,  // get_const(index) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_function__SearchByLabel_Event__request,  // get(index) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__fetch_function__SearchByLabel_Event__request,  // fetch(index, &value) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__assign_function__SearchByLabel_Event__request,  // assign(index, value) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__resize_function__SearchByLabel_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(waffle_agent_msgs__srv__SearchByLabel_Event, response),  // bytes offset in struct
    NULL,  // default value
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__size_function__SearchByLabel_Event__response,  // size() function pointer
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_const_function__SearchByLabel_Event__response,  // get_const(index) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__get_function__SearchByLabel_Event__response,  // get(index) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__fetch_function__SearchByLabel_Event__response,  // fetch(index, &value) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__assign_function__SearchByLabel_Event__response,  // assign(index, value) function pointer
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__resize_function__SearchByLabel_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_members = {
  "waffle_agent_msgs__srv",  // message namespace
  "SearchByLabel_Event",  // message name
  3,  // number of fields
  sizeof(waffle_agent_msgs__srv__SearchByLabel_Event),
  false,  // has_any_key_member_
  waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_member_array,  // message members
  waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_type_support_handle = {
  0,
  &waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_members,
  get_message_typesupport_handle_function,
  &waffle_agent_msgs__srv__SearchByLabel_Event__get_type_hash,
  &waffle_agent_msgs__srv__SearchByLabel_Event__get_type_description,
  &waffle_agent_msgs__srv__SearchByLabel_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_waffle_agent_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel_Event)() {
  waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel_Request)();
  waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel_Response)();
  if (!waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_type_support_handle.typesupport_identifier) {
    waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "waffle_agent_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers waffle_agent_msgs__srv__detail__search_by_label__rosidl_typesupport_introspection_c__SearchByLabel_service_members = {
  "waffle_agent_msgs__srv",  // service namespace
  "SearchByLabel",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // waffle_agent_msgs__srv__detail__search_by_label__rosidl_typesupport_introspection_c__SearchByLabel_Request_message_type_support_handle,
  NULL,  // response message
  // waffle_agent_msgs__srv__detail__search_by_label__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_type_support_handle
  NULL  // event_message
  // waffle_agent_msgs__srv__detail__search_by_label__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_type_support_handle
};


static rosidl_service_type_support_t waffle_agent_msgs__srv__detail__search_by_label__rosidl_typesupport_introspection_c__SearchByLabel_service_type_support_handle = {
  0,
  &waffle_agent_msgs__srv__detail__search_by_label__rosidl_typesupport_introspection_c__SearchByLabel_service_members,
  get_service_typesupport_handle_function,
  &waffle_agent_msgs__srv__SearchByLabel_Request__rosidl_typesupport_introspection_c__SearchByLabel_Request_message_type_support_handle,
  &waffle_agent_msgs__srv__SearchByLabel_Response__rosidl_typesupport_introspection_c__SearchByLabel_Response_message_type_support_handle,
  &waffle_agent_msgs__srv__SearchByLabel_Event__rosidl_typesupport_introspection_c__SearchByLabel_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    waffle_agent_msgs,
    srv,
    SearchByLabel
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    waffle_agent_msgs,
    srv,
    SearchByLabel
  ),
  &waffle_agent_msgs__srv__SearchByLabel__get_type_hash,
  &waffle_agent_msgs__srv__SearchByLabel__get_type_description,
  &waffle_agent_msgs__srv__SearchByLabel__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_waffle_agent_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel)(void) {
  if (!waffle_agent_msgs__srv__detail__search_by_label__rosidl_typesupport_introspection_c__SearchByLabel_service_type_support_handle.typesupport_identifier) {
    waffle_agent_msgs__srv__detail__search_by_label__rosidl_typesupport_introspection_c__SearchByLabel_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)waffle_agent_msgs__srv__detail__search_by_label__rosidl_typesupport_introspection_c__SearchByLabel_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, waffle_agent_msgs, srv, SearchByLabel_Event)()->data;
  }

  return &waffle_agent_msgs__srv__detail__search_by_label__rosidl_typesupport_introspection_c__SearchByLabel_service_type_support_handle;
}
