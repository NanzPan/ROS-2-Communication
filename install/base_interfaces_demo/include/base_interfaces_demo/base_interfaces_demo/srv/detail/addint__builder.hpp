// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from base_interfaces_demo:srv/Addint.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES_DEMO__SRV__DETAIL__ADDINT__BUILDER_HPP_
#define BASE_INTERFACES_DEMO__SRV__DETAIL__ADDINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "base_interfaces_demo/srv/detail/addint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace base_interfaces_demo
{

namespace srv
{

namespace builder
{

class Init_Addint_Request_num2
{
public:
  explicit Init_Addint_Request_num2(::base_interfaces_demo::srv::Addint_Request & msg)
  : msg_(msg)
  {}
  ::base_interfaces_demo::srv::Addint_Request num2(::base_interfaces_demo::srv::Addint_Request::_num2_type arg)
  {
    msg_.num2 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interfaces_demo::srv::Addint_Request msg_;
};

class Init_Addint_Request_num1
{
public:
  Init_Addint_Request_num1()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Addint_Request_num2 num1(::base_interfaces_demo::srv::Addint_Request::_num1_type arg)
  {
    msg_.num1 = std::move(arg);
    return Init_Addint_Request_num2(msg_);
  }

private:
  ::base_interfaces_demo::srv::Addint_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interfaces_demo::srv::Addint_Request>()
{
  return base_interfaces_demo::srv::builder::Init_Addint_Request_num1();
}

}  // namespace base_interfaces_demo


namespace base_interfaces_demo
{

namespace srv
{

namespace builder
{

class Init_Addint_Response_num3
{
public:
  Init_Addint_Response_num3()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::base_interfaces_demo::srv::Addint_Response num3(::base_interfaces_demo::srv::Addint_Response::_num3_type arg)
  {
    msg_.num3 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interfaces_demo::srv::Addint_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interfaces_demo::srv::Addint_Response>()
{
  return base_interfaces_demo::srv::builder::Init_Addint_Response_num3();
}

}  // namespace base_interfaces_demo

#endif  // BASE_INTERFACES_DEMO__SRV__DETAIL__ADDINT__BUILDER_HPP_
