// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from base_interfaces_demo:srv/Addint.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "base_interfaces_demo/srv/detail/addint__struct.h"
#include "base_interfaces_demo/srv/detail/addint__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace base_interfaces_demo
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _Addint_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Addint_Request_type_support_ids_t;

static const _Addint_Request_type_support_ids_t _Addint_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Addint_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Addint_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Addint_Request_type_support_symbol_names_t _Addint_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, base_interfaces_demo, srv, Addint_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, base_interfaces_demo, srv, Addint_Request)),
  }
};

typedef struct _Addint_Request_type_support_data_t
{
  void * data[2];
} _Addint_Request_type_support_data_t;

static _Addint_Request_type_support_data_t _Addint_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Addint_Request_message_typesupport_map = {
  2,
  "base_interfaces_demo",
  &_Addint_Request_message_typesupport_ids.typesupport_identifier[0],
  &_Addint_Request_message_typesupport_symbol_names.symbol_name[0],
  &_Addint_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Addint_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Addint_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace base_interfaces_demo

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, base_interfaces_demo, srv, Addint_Request)() {
  return &::base_interfaces_demo::srv::rosidl_typesupport_c::Addint_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "base_interfaces_demo/srv/detail/addint__struct.h"
// already included above
// #include "base_interfaces_demo/srv/detail/addint__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace base_interfaces_demo
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _Addint_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Addint_Response_type_support_ids_t;

static const _Addint_Response_type_support_ids_t _Addint_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Addint_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Addint_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Addint_Response_type_support_symbol_names_t _Addint_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, base_interfaces_demo, srv, Addint_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, base_interfaces_demo, srv, Addint_Response)),
  }
};

typedef struct _Addint_Response_type_support_data_t
{
  void * data[2];
} _Addint_Response_type_support_data_t;

static _Addint_Response_type_support_data_t _Addint_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Addint_Response_message_typesupport_map = {
  2,
  "base_interfaces_demo",
  &_Addint_Response_message_typesupport_ids.typesupport_identifier[0],
  &_Addint_Response_message_typesupport_symbol_names.symbol_name[0],
  &_Addint_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Addint_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Addint_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace base_interfaces_demo

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, base_interfaces_demo, srv, Addint_Response)() {
  return &::base_interfaces_demo::srv::rosidl_typesupport_c::Addint_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "base_interfaces_demo/srv/detail/addint__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace base_interfaces_demo
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _Addint_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Addint_type_support_ids_t;

static const _Addint_type_support_ids_t _Addint_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Addint_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Addint_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Addint_type_support_symbol_names_t _Addint_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, base_interfaces_demo, srv, Addint)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, base_interfaces_demo, srv, Addint)),
  }
};

typedef struct _Addint_type_support_data_t
{
  void * data[2];
} _Addint_type_support_data_t;

static _Addint_type_support_data_t _Addint_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Addint_service_typesupport_map = {
  2,
  "base_interfaces_demo",
  &_Addint_service_typesupport_ids.typesupport_identifier[0],
  &_Addint_service_typesupport_symbol_names.symbol_name[0],
  &_Addint_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t Addint_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Addint_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace base_interfaces_demo

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, base_interfaces_demo, srv, Addint)() {
  return &::base_interfaces_demo::srv::rosidl_typesupport_c::Addint_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
