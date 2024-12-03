// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from fishros_cpp:msg/SystemStatus.idl
// generated code does not contain a copyright notice

#ifndef FISHROS_CPP__MSG__DETAIL__SYSTEM_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define FISHROS_CPP__MSG__DETAIL__SYSTEM_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "fishros_cpp/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "fishros_cpp/msg/detail/system_status__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace fishros_cpp
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fishros_cpp
cdr_serialize(
  const fishros_cpp::msg::SystemStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fishros_cpp
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  fishros_cpp::msg::SystemStatus & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fishros_cpp
get_serialized_size(
  const fishros_cpp::msg::SystemStatus & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fishros_cpp
max_serialized_size_SystemStatus(
  bool & full_bounded,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace fishros_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fishros_cpp
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, fishros_cpp, msg, SystemStatus)();

#ifdef __cplusplus
}
#endif

#endif  // FISHROS_CPP__MSG__DETAIL__SYSTEM_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
