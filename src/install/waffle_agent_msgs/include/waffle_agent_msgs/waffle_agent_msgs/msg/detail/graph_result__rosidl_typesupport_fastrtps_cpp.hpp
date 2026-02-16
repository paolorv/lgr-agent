// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from waffle_agent_msgs:msg/GraphResult.idl
// generated code does not contain a copyright notice

#ifndef WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "waffle_agent_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "waffle_agent_msgs/msg/detail/graph_result__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace waffle_agent_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_waffle_agent_msgs
cdr_serialize(
  const waffle_agent_msgs::msg::GraphResult & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_waffle_agent_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  waffle_agent_msgs::msg::GraphResult & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_waffle_agent_msgs
get_serialized_size(
  const waffle_agent_msgs::msg::GraphResult & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_waffle_agent_msgs
max_serialized_size_GraphResult(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_waffle_agent_msgs
cdr_serialize_key(
  const waffle_agent_msgs::msg::GraphResult & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_waffle_agent_msgs
get_serialized_size_key(
  const waffle_agent_msgs::msg::GraphResult & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_waffle_agent_msgs
max_serialized_size_key_GraphResult(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace waffle_agent_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_waffle_agent_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, waffle_agent_msgs, msg, GraphResult)();

#ifdef __cplusplus
}
#endif

#endif  // WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
