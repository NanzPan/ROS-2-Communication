// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from base_interfaces_demo:srv/Addint.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES_DEMO__SRV__DETAIL__ADDINT__TRAITS_HPP_
#define BASE_INTERFACES_DEMO__SRV__DETAIL__ADDINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "base_interfaces_demo/srv/detail/addint__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace base_interfaces_demo
{

namespace srv
{

inline void to_flow_style_yaml(
  const Addint_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: num1
  {
    out << "num1: ";
    rosidl_generator_traits::value_to_yaml(msg.num1, out);
    out << ", ";
  }

  // member: num2
  {
    out << "num2: ";
    rosidl_generator_traits::value_to_yaml(msg.num2, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Addint_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: num1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num1: ";
    rosidl_generator_traits::value_to_yaml(msg.num1, out);
    out << "\n";
  }

  // member: num2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num2: ";
    rosidl_generator_traits::value_to_yaml(msg.num2, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Addint_Request & msg, bool use_flow_style = false)
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

}  // namespace base_interfaces_demo

namespace rosidl_generator_traits
{

[[deprecated("use base_interfaces_demo::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const base_interfaces_demo::srv::Addint_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  base_interfaces_demo::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use base_interfaces_demo::srv::to_yaml() instead")]]
inline std::string to_yaml(const base_interfaces_demo::srv::Addint_Request & msg)
{
  return base_interfaces_demo::srv::to_yaml(msg);
}

template<>
inline const char * data_type<base_interfaces_demo::srv::Addint_Request>()
{
  return "base_interfaces_demo::srv::Addint_Request";
}

template<>
inline const char * name<base_interfaces_demo::srv::Addint_Request>()
{
  return "base_interfaces_demo/srv/Addint_Request";
}

template<>
struct has_fixed_size<base_interfaces_demo::srv::Addint_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<base_interfaces_demo::srv::Addint_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<base_interfaces_demo::srv::Addint_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace base_interfaces_demo
{

namespace srv
{

inline void to_flow_style_yaml(
  const Addint_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: num3
  {
    out << "num3: ";
    rosidl_generator_traits::value_to_yaml(msg.num3, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Addint_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: num3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num3: ";
    rosidl_generator_traits::value_to_yaml(msg.num3, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Addint_Response & msg, bool use_flow_style = false)
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

}  // namespace base_interfaces_demo

namespace rosidl_generator_traits
{

[[deprecated("use base_interfaces_demo::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const base_interfaces_demo::srv::Addint_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  base_interfaces_demo::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use base_interfaces_demo::srv::to_yaml() instead")]]
inline std::string to_yaml(const base_interfaces_demo::srv::Addint_Response & msg)
{
  return base_interfaces_demo::srv::to_yaml(msg);
}

template<>
inline const char * data_type<base_interfaces_demo::srv::Addint_Response>()
{
  return "base_interfaces_demo::srv::Addint_Response";
}

template<>
inline const char * name<base_interfaces_demo::srv::Addint_Response>()
{
  return "base_interfaces_demo/srv/Addint_Response";
}

template<>
struct has_fixed_size<base_interfaces_demo::srv::Addint_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<base_interfaces_demo::srv::Addint_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<base_interfaces_demo::srv::Addint_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<base_interfaces_demo::srv::Addint>()
{
  return "base_interfaces_demo::srv::Addint";
}

template<>
inline const char * name<base_interfaces_demo::srv::Addint>()
{
  return "base_interfaces_demo/srv/Addint";
}

template<>
struct has_fixed_size<base_interfaces_demo::srv::Addint>
  : std::integral_constant<
    bool,
    has_fixed_size<base_interfaces_demo::srv::Addint_Request>::value &&
    has_fixed_size<base_interfaces_demo::srv::Addint_Response>::value
  >
{
};

template<>
struct has_bounded_size<base_interfaces_demo::srv::Addint>
  : std::integral_constant<
    bool,
    has_bounded_size<base_interfaces_demo::srv::Addint_Request>::value &&
    has_bounded_size<base_interfaces_demo::srv::Addint_Response>::value
  >
{
};

template<>
struct is_service<base_interfaces_demo::srv::Addint>
  : std::true_type
{
};

template<>
struct is_service_request<base_interfaces_demo::srv::Addint_Request>
  : std::true_type
{
};

template<>
struct is_service_response<base_interfaces_demo::srv::Addint_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // BASE_INTERFACES_DEMO__SRV__DETAIL__ADDINT__TRAITS_HPP_
