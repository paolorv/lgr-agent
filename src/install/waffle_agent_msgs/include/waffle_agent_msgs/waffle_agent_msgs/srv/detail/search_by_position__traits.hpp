// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from waffle_agent_msgs:srv/SearchByPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "waffle_agent_msgs/srv/search_by_position.hpp"


#ifndef WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__TRAITS_HPP_
#define WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "waffle_agent_msgs/srv/detail/search_by_position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace waffle_agent_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SearchByPosition_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: query_position
  {
    if (msg.query_position.size() == 0) {
      out << "query_position: []";
    } else {
      out << "query_position: [";
      size_t pending_items = msg.query_position.size();
      for (auto item : msg.query_position) {
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
  const SearchByPosition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: query_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.query_position.size() == 0) {
      out << "query_position: []\n";
    } else {
      out << "query_position:\n";
      for (auto item : msg.query_position) {
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

inline std::string to_yaml(const SearchByPosition_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace waffle_agent_msgs

namespace rosidl_generator_traits
{

[[deprecated("use waffle_agent_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const waffle_agent_msgs::srv::SearchByPosition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  waffle_agent_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use waffle_agent_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const waffle_agent_msgs::srv::SearchByPosition_Request & msg)
{
  return waffle_agent_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<waffle_agent_msgs::srv::SearchByPosition_Request>()
{
  return "waffle_agent_msgs::srv::SearchByPosition_Request";
}

template<>
inline const char * name<waffle_agent_msgs::srv::SearchByPosition_Request>()
{
  return "waffle_agent_msgs/srv/SearchByPosition_Request";
}

template<>
struct has_fixed_size<waffle_agent_msgs::srv::SearchByPosition_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<waffle_agent_msgs::srv::SearchByPosition_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<waffle_agent_msgs::srv::SearchByPosition_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'top_k_results'
#include "waffle_agent_msgs/msg/detail/graph_result__traits.hpp"

namespace waffle_agent_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SearchByPosition_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: top_k_results
  {
    if (msg.top_k_results.size() == 0) {
      out << "top_k_results: []";
    } else {
      out << "top_k_results: [";
      size_t pending_items = msg.top_k_results.size();
      for (auto item : msg.top_k_results) {
        to_flow_style_yaml(item, out);
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
  const SearchByPosition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: top_k_results
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.top_k_results.size() == 0) {
      out << "top_k_results: []\n";
    } else {
      out << "top_k_results:\n";
      for (auto item : msg.top_k_results) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SearchByPosition_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace waffle_agent_msgs

namespace rosidl_generator_traits
{

[[deprecated("use waffle_agent_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const waffle_agent_msgs::srv::SearchByPosition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  waffle_agent_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use waffle_agent_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const waffle_agent_msgs::srv::SearchByPosition_Response & msg)
{
  return waffle_agent_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<waffle_agent_msgs::srv::SearchByPosition_Response>()
{
  return "waffle_agent_msgs::srv::SearchByPosition_Response";
}

template<>
inline const char * name<waffle_agent_msgs::srv::SearchByPosition_Response>()
{
  return "waffle_agent_msgs/srv/SearchByPosition_Response";
}

template<>
struct has_fixed_size<waffle_agent_msgs::srv::SearchByPosition_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<waffle_agent_msgs::srv::SearchByPosition_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<waffle_agent_msgs::srv::SearchByPosition_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace waffle_agent_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SearchByPosition_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
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
  const SearchByPosition_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SearchByPosition_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace waffle_agent_msgs

namespace rosidl_generator_traits
{

[[deprecated("use waffle_agent_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const waffle_agent_msgs::srv::SearchByPosition_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  waffle_agent_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use waffle_agent_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const waffle_agent_msgs::srv::SearchByPosition_Event & msg)
{
  return waffle_agent_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<waffle_agent_msgs::srv::SearchByPosition_Event>()
{
  return "waffle_agent_msgs::srv::SearchByPosition_Event";
}

template<>
inline const char * name<waffle_agent_msgs::srv::SearchByPosition_Event>()
{
  return "waffle_agent_msgs/srv/SearchByPosition_Event";
}

template<>
struct has_fixed_size<waffle_agent_msgs::srv::SearchByPosition_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<waffle_agent_msgs::srv::SearchByPosition_Event>
  : std::integral_constant<bool, has_bounded_size<service_msgs::msg::ServiceEventInfo>::value && has_bounded_size<waffle_agent_msgs::srv::SearchByPosition_Request>::value && has_bounded_size<waffle_agent_msgs::srv::SearchByPosition_Response>::value> {};

template<>
struct is_message<waffle_agent_msgs::srv::SearchByPosition_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<waffle_agent_msgs::srv::SearchByPosition>()
{
  return "waffle_agent_msgs::srv::SearchByPosition";
}

template<>
inline const char * name<waffle_agent_msgs::srv::SearchByPosition>()
{
  return "waffle_agent_msgs/srv/SearchByPosition";
}

template<>
struct has_fixed_size<waffle_agent_msgs::srv::SearchByPosition>
  : std::integral_constant<
    bool,
    has_fixed_size<waffle_agent_msgs::srv::SearchByPosition_Request>::value &&
    has_fixed_size<waffle_agent_msgs::srv::SearchByPosition_Response>::value
  >
{
};

template<>
struct has_bounded_size<waffle_agent_msgs::srv::SearchByPosition>
  : std::integral_constant<
    bool,
    has_bounded_size<waffle_agent_msgs::srv::SearchByPosition_Request>::value &&
    has_bounded_size<waffle_agent_msgs::srv::SearchByPosition_Response>::value
  >
{
};

template<>
struct is_service<waffle_agent_msgs::srv::SearchByPosition>
  : std::true_type
{
};

template<>
struct is_service_request<waffle_agent_msgs::srv::SearchByPosition_Request>
  : std::true_type
{
};

template<>
struct is_service_response<waffle_agent_msgs::srv::SearchByPosition_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__TRAITS_HPP_
