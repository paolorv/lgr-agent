// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from waffle_agent_msgs:msg/GraphResult.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "waffle_agent_msgs/msg/graph_result.hpp"


#ifndef WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__TRAITS_HPP_
#define WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "waffle_agent_msgs/msg/detail/graph_result__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace waffle_agent_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const GraphResult & msg,
  std::ostream & out)
{
  out << "{";
  // member: node_id
  {
    out << "node_id: ";
    rosidl_generator_traits::value_to_yaml(msg.node_id, out);
    out << ", ";
  }

  // member: label
  {
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << ", ";
  }

  // member: score
  {
    out << "score: ";
    rosidl_generator_traits::value_to_yaml(msg.score, out);
    out << ", ";
  }

  // member: position
  {
    if (msg.position.size() == 0) {
      out << "position: []";
    } else {
      out << "position: [";
      size_t pending_items = msg.position.size();
      for (auto item : msg.position) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GraphResult & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: node_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "node_id: ";
    rosidl_generator_traits::value_to_yaml(msg.node_id, out);
    out << "\n";
  }

  // member: label
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << "\n";
  }

  // member: score
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "score: ";
    rosidl_generator_traits::value_to_yaml(msg.score, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.position.size() == 0) {
      out << "position: []\n";
    } else {
      out << "position:\n";
      for (auto item : msg.position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GraphResult & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace waffle_agent_msgs

namespace rosidl_generator_traits
{

[[deprecated("use waffle_agent_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const waffle_agent_msgs::msg::GraphResult & msg,
  std::ostream & out, size_t indentation = 0)
{
  waffle_agent_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use waffle_agent_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const waffle_agent_msgs::msg::GraphResult & msg)
{
  return waffle_agent_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<waffle_agent_msgs::msg::GraphResult>()
{
  return "waffle_agent_msgs::msg::GraphResult";
}

template<>
inline const char * name<waffle_agent_msgs::msg::GraphResult>()
{
  return "waffle_agent_msgs/msg/GraphResult";
}

template<>
struct has_fixed_size<waffle_agent_msgs::msg::GraphResult>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<waffle_agent_msgs::msg::GraphResult>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<waffle_agent_msgs::msg::GraphResult>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__TRAITS_HPP_
