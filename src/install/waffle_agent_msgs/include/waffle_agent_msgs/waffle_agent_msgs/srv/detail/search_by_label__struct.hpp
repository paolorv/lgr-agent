// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from waffle_agent_msgs:srv/SearchByLabel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "waffle_agent_msgs/srv/search_by_label.hpp"


#ifndef WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_LABEL__STRUCT_HPP_
#define WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_LABEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Request __attribute__((deprecated))
#else
# define DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Request __declspec(deprecated)
#endif

namespace waffle_agent_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SearchByLabel_Request_
{
  using Type = SearchByLabel_Request_<ContainerAllocator>;

  explicit SearchByLabel_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->query_text = "";
    }
  }

  explicit SearchByLabel_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : query_text(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->query_text = "";
    }
  }

  // field types and members
  using _query_text_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _query_text_type query_text;

  // setters for named parameter idiom
  Type & set__query_text(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->query_text = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Request
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Request
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SearchByLabel_Request_ & other) const
  {
    if (this->query_text != other.query_text) {
      return false;
    }
    return true;
  }
  bool operator!=(const SearchByLabel_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SearchByLabel_Request_

// alias to use template instance with default allocator
using SearchByLabel_Request =
  waffle_agent_msgs::srv::SearchByLabel_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace waffle_agent_msgs


// Include directives for member types
// Member 'top_k_results'
#include "waffle_agent_msgs/msg/detail/graph_result__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Response __attribute__((deprecated))
#else
# define DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Response __declspec(deprecated)
#endif

namespace waffle_agent_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SearchByLabel_Response_
{
  using Type = SearchByLabel_Response_<ContainerAllocator>;

  explicit SearchByLabel_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit SearchByLabel_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _top_k_results_type =
    std::vector<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator>>>;
  _top_k_results_type top_k_results;

  // setters for named parameter idiom
  Type & set__top_k_results(
    const std::vector<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<waffle_agent_msgs::msg::GraphResult_<ContainerAllocator>>> & _arg)
  {
    this->top_k_results = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Response
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Response
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SearchByLabel_Response_ & other) const
  {
    if (this->top_k_results != other.top_k_results) {
      return false;
    }
    return true;
  }
  bool operator!=(const SearchByLabel_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SearchByLabel_Response_

// alias to use template instance with default allocator
using SearchByLabel_Response =
  waffle_agent_msgs::srv::SearchByLabel_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace waffle_agent_msgs


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Event __attribute__((deprecated))
#else
# define DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Event __declspec(deprecated)
#endif

namespace waffle_agent_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SearchByLabel_Event_
{
  using Type = SearchByLabel_Event_<ContainerAllocator>;

  explicit SearchByLabel_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit SearchByLabel_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<waffle_agent_msgs::srv::SearchByLabel_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<waffle_agent_msgs::srv::SearchByLabel_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Event
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__waffle_agent_msgs__srv__SearchByLabel_Event
    std::shared_ptr<waffle_agent_msgs::srv::SearchByLabel_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SearchByLabel_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const SearchByLabel_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SearchByLabel_Event_

// alias to use template instance with default allocator
using SearchByLabel_Event =
  waffle_agent_msgs::srv::SearchByLabel_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace waffle_agent_msgs

namespace waffle_agent_msgs
{

namespace srv
{

struct SearchByLabel
{
  using Request = waffle_agent_msgs::srv::SearchByLabel_Request;
  using Response = waffle_agent_msgs::srv::SearchByLabel_Response;
  using Event = waffle_agent_msgs::srv::SearchByLabel_Event;
};

}  // namespace srv

}  // namespace waffle_agent_msgs

#endif  // WAFFLE_AGENT_MSGS__SRV__DETAIL__SEARCH_BY_LABEL__STRUCT_HPP_
