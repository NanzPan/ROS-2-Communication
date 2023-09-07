// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from base_interfaces_demo:srv/Addint.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES_DEMO__SRV__DETAIL__ADDINT__STRUCT_H_
#define BASE_INTERFACES_DEMO__SRV__DETAIL__ADDINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/Addint in the package base_interfaces_demo.
typedef struct base_interfaces_demo__srv__Addint_Request
{
  int32_t num1;
  int32_t num2;
} base_interfaces_demo__srv__Addint_Request;

// Struct for a sequence of base_interfaces_demo__srv__Addint_Request.
typedef struct base_interfaces_demo__srv__Addint_Request__Sequence
{
  base_interfaces_demo__srv__Addint_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces_demo__srv__Addint_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/Addint in the package base_interfaces_demo.
typedef struct base_interfaces_demo__srv__Addint_Response
{
  int32_t num3;
} base_interfaces_demo__srv__Addint_Response;

// Struct for a sequence of base_interfaces_demo__srv__Addint_Response.
typedef struct base_interfaces_demo__srv__Addint_Response__Sequence
{
  base_interfaces_demo__srv__Addint_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces_demo__srv__Addint_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BASE_INTERFACES_DEMO__SRV__DETAIL__ADDINT__STRUCT_H_
