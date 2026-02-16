// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from waffle_agent_msgs:srv/SearchByLabel.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "waffle_agent_msgs/srv/detail/search_by_label__functions.h"
#include "waffle_agent_msgs/srv/detail/search_by_label__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace waffle_agent_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void SearchByLabel_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) waffle_agent_msgs::srv::SearchByLabel_Request(_init);
}

void SearchByLabel_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<waffle_agent_msgs::srv::SearchByLabel_Request *>(message_memory);
  typed_message->~SearchByLabel_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SearchByLabel_Request_message_member_array[1] = {
  {
    "query_text",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(waffle_agent_msgs::srv::SearchByLabel_Request, query_text),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SearchByLabel_Request_message_members = {
  "waffle_agent_msgs::srv",  // message namespace
  "SearchByLabel_Request",  // message name
  1,  // number of fields
  sizeof(waffle_agent_msgs::srv::SearchByLabel_Request),
  false,  // has_any_key_member_
  SearchByLabel_Request_message_member_array,  // message members
  SearchByLabel_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  SearchByLabel_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SearchByLabel_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SearchByLabel_Request_message_members,
  get_message_typesupport_handle_function,
  &waffle_agent_msgs__srv__SearchByLabel_Request__get_type_hash,
  &waffle_agent_msgs__srv__SearchByLabel_Request__get_type_description,
  &waffle_agent_msgs__srv__SearchByLabel_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace waffle_agent_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<waffle_agent_msgs::srv::SearchByLabel_Request>()
{
  return &::waffle_agent_msgs::srv::rosidl_typesupport_introspection_cpp::SearchByLabel_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, waffle_agent_msgs, srv, SearchByLabel_Request)() {
  return &::waffle_agent_msgs::srv::rosidl_typesupport_introspection_cpp::SearchByLabel_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__functions.h"
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace waffle_agent_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void SearchByLabel_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) waffle_agent_msgs::srv::SearchByLabel_Response(_init);
}

void SearchByLabel_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<waffle_agent_msgs::srv::SearchByLabel_Response *>(message_memory);
  typed_message->~SearchByLabel_Response();
}

size_t size_function__SearchByLabel_Response__top_k_results(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<waffle_agent_msgs::msg::GraphResult> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SearchByLabel_Response__top_k_results(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<waffle_agent_msgs::msg::GraphResult> *>(untyped_member);
  return &member[index];
}

void * get_function__SearchByLabel_Response__top_k_results(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<waffle_agent_msgs::msg::GraphResult> *>(untyped_member);
  return &member[index];
}

void fetch_function__SearchByLabel_Response__top_k_results(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const waffle_agent_msgs::msg::GraphResult *>(
    get_const_function__SearchByLabel_Response__top_k_results(untyped_member, index));
  auto & value = *reinterpret_cast<waffle_agent_msgs::msg::GraphResult *>(untyped_value);
  value = item;
}

void assign_function__SearchByLabel_Response__top_k_results(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<waffle_agent_msgs::msg::GraphResult *>(
    get_function__SearchByLabel_Response__top_k_results(untyped_member, index));
  const auto & value = *reinterpret_cast<const waffle_agent_msgs::msg::GraphResult *>(untyped_value);
  item = value;
}

void resize_function__SearchByLabel_Response__top_k_results(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<waffle_agent_msgs::msg::GraphResult> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SearchByLabel_Response_message_member_array[1] = {
  {
    "top_k_results",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<waffle_agent_msgs::msg::GraphResult>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(waffle_agent_msgs::srv::SearchByLabel_Response, top_k_results),  // bytes offset in struct
    nullptr,  // default value
    size_function__SearchByLabel_Response__top_k_results,  // size() function pointer
    get_const_function__SearchByLabel_Response__top_k_results,  // get_const(index) function pointer
    get_function__SearchByLabel_Response__top_k_results,  // get(index) function pointer
    fetch_function__SearchByLabel_Response__top_k_results,  // fetch(index, &value) function pointer
    assign_function__SearchByLabel_Response__top_k_results,  // assign(index, value) function pointer
    resize_function__SearchByLabel_Response__top_k_results  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SearchByLabel_Response_message_members = {
  "waffle_agent_msgs::srv",  // message namespace
  "SearchByLabel_Response",  // message name
  1,  // number of fields
  sizeof(waffle_agent_msgs::srv::SearchByLabel_Response),
  false,  // has_any_key_member_
  SearchByLabel_Response_message_member_array,  // message members
  SearchByLabel_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  SearchByLabel_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SearchByLabel_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SearchByLabel_Response_message_members,
  get_message_typesupport_handle_function,
  &waffle_agent_msgs__srv__SearchByLabel_Response__get_type_hash,
  &waffle_agent_msgs__srv__SearchByLabel_Response__get_type_description,
  &waffle_agent_msgs__srv__SearchByLabel_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace waffle_agent_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<waffle_agent_msgs::srv::SearchByLabel_Response>()
{
  return &::waffle_agent_msgs::srv::rosidl_typesupport_introspection_cpp::SearchByLabel_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, waffle_agent_msgs, srv, SearchByLabel_Response)() {
  return &::waffle_agent_msgs::srv::rosidl_typesupport_introspection_cpp::SearchByLabel_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__functions.h"
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace waffle_agent_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void SearchByLabel_Event_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) waffle_agent_msgs::srv::SearchByLabel_Event(_init);
}

void SearchByLabel_Event_fini_function(void * message_memory)
{
  auto typed_message = static_cast<waffle_agent_msgs::srv::SearchByLabel_Event *>(message_memory);
  typed_message->~SearchByLabel_Event();
}

size_t size_function__SearchByLabel_Event__request(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<waffle_agent_msgs::srv::SearchByLabel_Request> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SearchByLabel_Event__request(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<waffle_agent_msgs::srv::SearchByLabel_Request> *>(untyped_member);
  return &member[index];
}

void * get_function__SearchByLabel_Event__request(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<waffle_agent_msgs::srv::SearchByLabel_Request> *>(untyped_member);
  return &member[index];
}

void fetch_function__SearchByLabel_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const waffle_agent_msgs::srv::SearchByLabel_Request *>(
    get_const_function__SearchByLabel_Event__request(untyped_member, index));
  auto & value = *reinterpret_cast<waffle_agent_msgs::srv::SearchByLabel_Request *>(untyped_value);
  value = item;
}

void assign_function__SearchByLabel_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<waffle_agent_msgs::srv::SearchByLabel_Request *>(
    get_function__SearchByLabel_Event__request(untyped_member, index));
  const auto & value = *reinterpret_cast<const waffle_agent_msgs::srv::SearchByLabel_Request *>(untyped_value);
  item = value;
}

void resize_function__SearchByLabel_Event__request(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<waffle_agent_msgs::srv::SearchByLabel_Request> *>(untyped_member);
  member->resize(size);
}

size_t size_function__SearchByLabel_Event__response(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<waffle_agent_msgs::srv::SearchByLabel_Response> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SearchByLabel_Event__response(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<waffle_agent_msgs::srv::SearchByLabel_Response> *>(untyped_member);
  return &member[index];
}

void * get_function__SearchByLabel_Event__response(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<waffle_agent_msgs::srv::SearchByLabel_Response> *>(untyped_member);
  return &member[index];
}

void fetch_function__SearchByLabel_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const waffle_agent_msgs::srv::SearchByLabel_Response *>(
    get_const_function__SearchByLabel_Event__response(untyped_member, index));
  auto & value = *reinterpret_cast<waffle_agent_msgs::srv::SearchByLabel_Response *>(untyped_value);
  value = item;
}

void assign_function__SearchByLabel_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<waffle_agent_msgs::srv::SearchByLabel_Response *>(
    get_function__SearchByLabel_Event__response(untyped_member, index));
  const auto & value = *reinterpret_cast<const waffle_agent_msgs::srv::SearchByLabel_Response *>(untyped_value);
  item = value;
}

void resize_function__SearchByLabel_Event__response(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<waffle_agent_msgs::srv::SearchByLabel_Response> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SearchByLabel_Event_message_member_array[3] = {
  {
    "info",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<service_msgs::msg::ServiceEventInfo>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(waffle_agent_msgs::srv::SearchByLabel_Event, info),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "request",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<waffle_agent_msgs::srv::SearchByLabel_Request>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(waffle_agent_msgs::srv::SearchByLabel_Event, request),  // bytes offset in struct
    nullptr,  // default value
    size_function__SearchByLabel_Event__request,  // size() function pointer
    get_const_function__SearchByLabel_Event__request,  // get_const(index) function pointer
    get_function__SearchByLabel_Event__request,  // get(index) function pointer
    fetch_function__SearchByLabel_Event__request,  // fetch(index, &value) function pointer
    assign_function__SearchByLabel_Event__request,  // assign(index, value) function pointer
    resize_function__SearchByLabel_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<waffle_agent_msgs::srv::SearchByLabel_Response>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(waffle_agent_msgs::srv::SearchByLabel_Event, response),  // bytes offset in struct
    nullptr,  // default value
    size_function__SearchByLabel_Event__response,  // size() function pointer
    get_const_function__SearchByLabel_Event__response,  // get_const(index) function pointer
    get_function__SearchByLabel_Event__response,  // get(index) function pointer
    fetch_function__SearchByLabel_Event__response,  // fetch(index, &value) function pointer
    assign_function__SearchByLabel_Event__response,  // assign(index, value) function pointer
    resize_function__SearchByLabel_Event__response  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SearchByLabel_Event_message_members = {
  "waffle_agent_msgs::srv",  // message namespace
  "SearchByLabel_Event",  // message name
  3,  // number of fields
  sizeof(waffle_agent_msgs::srv::SearchByLabel_Event),
  false,  // has_any_key_member_
  SearchByLabel_Event_message_member_array,  // message members
  SearchByLabel_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  SearchByLabel_Event_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SearchByLabel_Event_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SearchByLabel_Event_message_members,
  get_message_typesupport_handle_function,
  &waffle_agent_msgs__srv__SearchByLabel_Event__get_type_hash,
  &waffle_agent_msgs__srv__SearchByLabel_Event__get_type_description,
  &waffle_agent_msgs__srv__SearchByLabel_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace waffle_agent_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<waffle_agent_msgs::srv::SearchByLabel_Event>()
{
  return &::waffle_agent_msgs::srv::rosidl_typesupport_introspection_cpp::SearchByLabel_Event_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, waffle_agent_msgs, srv, SearchByLabel_Event)() {
  return &::waffle_agent_msgs::srv::rosidl_typesupport_introspection_cpp::SearchByLabel_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__functions.h"
// already included above
// #include "waffle_agent_msgs/srv/detail/search_by_label__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace waffle_agent_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers SearchByLabel_service_members = {
  "waffle_agent_msgs::srv",  // service namespace
  "SearchByLabel",  // service name
  // the following fields are initialized below on first access
  // see get_service_type_support_handle<waffle_agent_msgs::srv::SearchByLabel>()
  nullptr,  // request message
  nullptr,  // response message
  nullptr,  // event message
};

static const rosidl_service_type_support_t SearchByLabel_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SearchByLabel_service_members,
  get_service_typesupport_handle_function,
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<waffle_agent_msgs::srv::SearchByLabel_Request>(),
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<waffle_agent_msgs::srv::SearchByLabel_Response>(),
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<waffle_agent_msgs::srv::SearchByLabel_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<waffle_agent_msgs::srv::SearchByLabel>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<waffle_agent_msgs::srv::SearchByLabel>,
  &waffle_agent_msgs__srv__SearchByLabel__get_type_hash,
  &waffle_agent_msgs__srv__SearchByLabel__get_type_description,
  &waffle_agent_msgs__srv__SearchByLabel__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace waffle_agent_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<waffle_agent_msgs::srv::SearchByLabel>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::waffle_agent_msgs::srv::rosidl_typesupport_introspection_cpp::SearchByLabel_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure all of the service_members are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr ||
    service_members->event_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::waffle_agent_msgs::srv::SearchByLabel_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::waffle_agent_msgs::srv::SearchByLabel_Response
      >()->data
      );
    // initialize the event_members_ with the static function from the external library
    service_members->event_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::waffle_agent_msgs::srv::SearchByLabel_Event
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, waffle_agent_msgs, srv, SearchByLabel)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<waffle_agent_msgs::srv::SearchByLabel>();
}

#ifdef __cplusplus
}
#endif
