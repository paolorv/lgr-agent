// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from waffle_agent_msgs:msg/GraphResult.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "waffle_agent_msgs/msg/graph_result.hpp"


#ifndef WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__BUILDER_HPP_
#define WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "waffle_agent_msgs/msg/detail/graph_result__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace waffle_agent_msgs
{

namespace msg
{

namespace builder
{

class Init_GraphResult_position
{
public:
  explicit Init_GraphResult_position(::waffle_agent_msgs::msg::GraphResult & msg)
  : msg_(msg)
  {}
  ::waffle_agent_msgs::msg::GraphResult position(::waffle_agent_msgs::msg::GraphResult::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::waffle_agent_msgs::msg::GraphResult msg_;
};

class Init_GraphResult_score
{
public:
  explicit Init_GraphResult_score(::waffle_agent_msgs::msg::GraphResult & msg)
  : msg_(msg)
  {}
  Init_GraphResult_position score(::waffle_agent_msgs::msg::GraphResult::_score_type arg)
  {
    msg_.score = std::move(arg);
    return Init_GraphResult_position(msg_);
  }

private:
  ::waffle_agent_msgs::msg::GraphResult msg_;
};

class Init_GraphResult_label
{
public:
  explicit Init_GraphResult_label(::waffle_agent_msgs::msg::GraphResult & msg)
  : msg_(msg)
  {}
  Init_GraphResult_score label(::waffle_agent_msgs::msg::GraphResult::_label_type arg)
  {
    msg_.label = std::move(arg);
    return Init_GraphResult_score(msg_);
  }

private:
  ::waffle_agent_msgs::msg::GraphResult msg_;
};

class Init_GraphResult_node_id
{
public:
  Init_GraphResult_node_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GraphResult_label node_id(::waffle_agent_msgs::msg::GraphResult::_node_id_type arg)
  {
    msg_.node_id = std::move(arg);
    return Init_GraphResult_label(msg_);
  }

private:
  ::waffle_agent_msgs::msg::GraphResult msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::waffle_agent_msgs::msg::GraphResult>()
{
  return waffle_agent_msgs::msg::builder::Init_GraphResult_node_id();
}

}  // namespace waffle_agent_msgs

#endif  // WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__BUILDER_HPP_
