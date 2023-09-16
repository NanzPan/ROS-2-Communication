// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from base_interfaces_demo:srv/Distance.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES_DEMO__SRV__DETAIL__DISTANCE__BUILDER_HPP_
#define BASE_INTERFACES_DEMO__SRV__DETAIL__DISTANCE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "base_interfaces_demo/srv/detail/distance__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace base_interfaces_demo
{

namespace srv
{

namespace builder
{

class Init_Distance_Request_theda
{
public:
  explicit Init_Distance_Request_theda(::base_interfaces_demo::srv::Distance_Request & msg)
  : msg_(msg)
  {}
  ::base_interfaces_demo::srv::Distance_Request theda(::base_interfaces_demo::srv::Distance_Request::_theda_type arg)
  {
    msg_.theda = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interfaces_demo::srv::Distance_Request msg_;
};

class Init_Distance_Request_y1
{
public:
  explicit Init_Distance_Request_y1(::base_interfaces_demo::srv::Distance_Request & msg)
  : msg_(msg)
  {}
  Init_Distance_Request_theda y1(::base_interfaces_demo::srv::Distance_Request::_y1_type arg)
  {
    msg_.y1 = std::move(arg);
    return Init_Distance_Request_theda(msg_);
  }

private:
  ::base_interfaces_demo::srv::Distance_Request msg_;
};

class Init_Distance_Request_x1
{
public:
  Init_Distance_Request_x1()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Distance_Request_y1 x1(::base_interfaces_demo::srv::Distance_Request::_x1_type arg)
  {
    msg_.x1 = std::move(arg);
    return Init_Distance_Request_y1(msg_);
  }

private:
  ::base_interfaces_demo::srv::Distance_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interfaces_demo::srv::Distance_Request>()
{
  return base_interfaces_demo::srv::builder::Init_Distance_Request_x1();
}

}  // namespace base_interfaces_demo


namespace base_interfaces_demo
{

namespace srv
{

namespace builder
{

class Init_Distance_Response_distance
{
public:
  Init_Distance_Response_distance()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::base_interfaces_demo::srv::Distance_Response distance(::base_interfaces_demo::srv::Distance_Response::_distance_type arg)
  {
    msg_.distance = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interfaces_demo::srv::Distance_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interfaces_demo::srv::Distance_Response>()
{
  return base_interfaces_demo::srv::builder::Init_Distance_Response_distance();
}

}  // namespace base_interfaces_demo

#endif  // BASE_INTERFACES_DEMO__SRV__DETAIL__DISTANCE__BUILDER_HPP_
