// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from waffle_agent_msgs:msg/GraphResult.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "waffle_agent_msgs/msg/graph_result.hpp"


#ifndef WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__STRUCT_HPP_
#define WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__waffle_agent_msgs__msg__GraphResult __attribute__((deprecated))
#else
# define DEPRECATED__waffle_agent_msgs__msg__GraphResult __declspec(deprecated)
#endif

namespace waffle_agent_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GraphResult_
{
  using Type = GraphResult_<ContainerAllocator>;

  explicit GraphResult_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->node_id = 0l;
      this->label = "";
      this->score = 0.0f;
    }
  }

  explicit GraphResult_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : label(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->node_id = 0l;
      this->label = "";
      this->score = 0.0f;
    }
  }

  // field types and members
  using _node_id_type =
    int32_t;
  _node_id_type node_id;
  using _label_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _label_type label;
  using _score_type =
    float;
  _score_type score;
  using _position_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _position_type position;

  // setters for named parameter idiom
  Type & set__node_id(
    const int32_t & _arg)
  {
    this->node_id = _arg;
    return *this;
  }
  Type & set__label(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->label = _arg;
    return *this;
  }
  Type & set__score(
    const float & _arg)
  {
    this->score = _arg;
    return *this;
  }
  Type & set__position(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->position = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    waffle_agent_msgs::msg::GraphResult_<ContainerAllocator> *;
  using ConstRawPtr =
    const waffle_agent_msgs::msg::GraphResult_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      waffle_agent_msgs::msg::GraphResult_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      waffle_agent_msgs::msg::GraphResult_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__waffle_agent_msgs__msg__GraphResult
    std::shared_ptr<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__waffle_agent_msgs__msg__GraphResult
    std::shared_ptr<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GraphResult_ & other) const
  {
    if (this->node_id != other.node_id) {
      return false;
    }
    if (this->label != other.label) {
      return false;
    }
    if (this->score != other.score) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    return true;
  }
  bool operator!=(const GraphResult_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GraphResult_

// alias to use template instance with default allocator
using GraphResult =
  waffle_agent_msgs::msg::GraphResult_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace waffle_agent_msgs

#endif  // WAFFLE_AGENT_MSGS__MSG__DETAIL__GRAPH_RESULT__STRUCT_HPP_
