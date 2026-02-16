// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from waffle_agent_msgs:srv/SearchByPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "waffle_agent_msgs/srv/search_by_position.hpp"


#ifndef WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__BUILDER_HPP_
#define WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "waffle_agent_msgs/srv/detail/search_by_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace waffle_agent_msgs
{

namespace srv
{

namespace builder
{

class Init_SearchByPosition_Request_query_position
{
public:
  Init_SearchByPosition_Request_query_position()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::waffle_agent_msgs::srv::SearchByPosition_Request query_position(::waffle_agent_msgs::srv::SearchByPosition_Request::_query_position_type arg)
  {
    msg_.query_position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::waffle_agent_msgs::srv::SearchByPosition_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::waffle_agent_msgs::srv::SearchByPosition_Request>()
{
  return waffle_agent_msgs::srv::builder::Init_SearchByPosition_Request_query_position();
}

}  // namespace waffle_agent_msgs


namespace waffle_agent_msgs
{

namespace srv
{

namespace builder
{

class Init_SearchByPosition_Response_top_k_results
{
public:
  Init_SearchByPosition_Response_top_k_results()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::waffle_agent_msgs::srv::SearchByPosition_Response top_k_results(::waffle_agent_msgs::srv::SearchByPosition_Response::_top_k_results_type arg)
  {
    msg_.top_k_results = std::move(arg);
    return std::move(msg_);
  }

private:
  ::waffle_agent_msgs::srv::SearchByPosition_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::waffle_agent_msgs::srv::SearchByPosition_Response>()
{
  return waffle_agent_msgs::srv::builder::Init_SearchByPosition_Response_top_k_results();
}

}  // namespace waffle_agent_msgs


namespace waffle_agent_msgs
{

namespace srv
{

namespace builder
{

class Init_SearchByPosition_Event_response
{
public:
  explicit Init_SearchByPosition_Event_response(::waffle_agent_msgs::srv::SearchByPosition_Event & msg)
  : msg_(msg)
  {}
  ::waffle_agent_msgs::srv::SearchByPosition_Event response(::waffle_agent_msgs::srv::SearchByPosition_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::waffle_agent_msgs::srv::SearchByPosition_Event msg_;
};

class Init_SearchByPosition_Event_request
{
public:
  explicit Init_SearchByPosition_Event_request(::waffle_agent_msgs::srv::SearchByPosition_Event & msg)
  : msg_(msg)
  {}
  Init_SearchByPosition_Event_response request(::waffle_agent_msgs::srv::SearchByPosition_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SearchByPosition_Event_response(msg_);
  }

private:
  ::waffle_agent_msgs::srv::SearchByPosition_Event msg_;
};

class Init_SearchByPosition_Event_info
{
public:
  Init_SearchByPosition_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SearchByPosition_Event_request info(::waffle_agent_msgs::srv::SearchByPosition_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SearchByPosition_Event_request(msg_);
  }

private:
  ::waffle_agent_msgs::srv::SearchByPosition_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::waffle_agent_msgs::srv::SearchByPosition_Event>()
{
  return waffle_agent_msgs::srv::builder::Init_SearchByPosition_Event_info();
}

}  // namespace waffle_agent_msgs

#endif  // WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_POSITION__BUILDER_HPP_
