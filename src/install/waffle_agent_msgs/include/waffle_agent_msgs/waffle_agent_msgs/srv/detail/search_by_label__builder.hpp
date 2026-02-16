// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from waffle_agent_msgs:srv/SearchByLabel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "waffle_agent_msgs/srv/search_by_label.hpp"


#ifndef WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_LABEL__BUILDER_HPP_
#define WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_LABEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "waffle_agent_msgs/srv/detail/search_by_label__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace waffle_agent_msgs
{

namespace srv
{

namespace builder
{

class Init_SearchByLabel_Request_query_text
{
public:
  Init_SearchByLabel_Request_query_text()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::waffle_agent_msgs::srv::SearchByLabel_Request query_text(::waffle_agent_msgs::srv::SearchByLabel_Request::_query_text_type arg)
  {
    msg_.query_text = std::move(arg);
    return std::move(msg_);
  }

private:
  ::waffle_agent_msgs::srv::SearchByLabel_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::waffle_agent_msgs::srv::SearchByLabel_Request>()
{
  return waffle_agent_msgs::srv::builder::Init_SearchByLabel_Request_query_text();
}

}  // namespace waffle_agent_msgs


namespace waffle_agent_msgs
{

namespace srv
{

namespace builder
{

class Init_SearchByLabel_Response_top_k_results
{
public:
  Init_SearchByLabel_Response_top_k_results()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::waffle_agent_msgs::srv::SearchByLabel_Response top_k_results(::waffle_agent_msgs::srv::SearchByLabel_Response::_top_k_results_type arg)
  {
    msg_.top_k_results = std::move(arg);
    return std::move(msg_);
  }

private:
  ::waffle_agent_msgs::srv::SearchByLabel_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::waffle_agent_msgs::srv::SearchByLabel_Response>()
{
  return waffle_agent_msgs::srv::builder::Init_SearchByLabel_Response_top_k_results();
}

}  // namespace waffle_agent_msgs


namespace waffle_agent_msgs
{

namespace srv
{

namespace builder
{

class Init_SearchByLabel_Event_response
{
public:
  explicit Init_SearchByLabel_Event_response(::waffle_agent_msgs::srv::SearchByLabel_Event & msg)
  : msg_(msg)
  {}
  ::waffle_agent_msgs::srv::SearchByLabel_Event response(::waffle_agent_msgs::srv::SearchByLabel_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::waffle_agent_msgs::srv::SearchByLabel_Event msg_;
};

class Init_SearchByLabel_Event_request
{
public:
  explicit Init_SearchByLabel_Event_request(::waffle_agent_msgs::srv::SearchByLabel_Event & msg)
  : msg_(msg)
  {}
  Init_SearchByLabel_Event_response request(::waffle_agent_msgs::srv::SearchByLabel_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SearchByLabel_Event_response(msg_);
  }

private:
  ::waffle_agent_msgs::srv::SearchByLabel_Event msg_;
};

class Init_SearchByLabel_Event_info
{
public:
  Init_SearchByLabel_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SearchByLabel_Event_request info(::waffle_agent_msgs::srv::SearchByLabel_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SearchByLabel_Event_request(msg_);
  }

private:
  ::waffle_agent_msgs::srv::SearchByLabel_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::waffle_agent_msgs::srv::SearchByLabel_Event>()
{
  return waffle_agent_msgs::srv::builder::Init_SearchByLabel_Event_info();
}

}  // namespace waffle_agent_msgs

#endif  // WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_LABEL__BUILDER_HPP_
