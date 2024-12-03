// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from fishros_cpp:msg/SystemStatus.idl
// generated code does not contain a copyright notice

#ifndef FISHROS_CPP__MSG__DETAIL__SYSTEM_STATUS__TRAITS_HPP_
#define FISHROS_CPP__MSG__DETAIL__SYSTEM_STATUS__TRAITS_HPP_

#include "fishros_cpp/msg/detail/system_status__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<fishros_cpp::msg::SystemStatus>()
{
  return "fishros_cpp::msg::SystemStatus";
}

template<>
inline const char * name<fishros_cpp::msg::SystemStatus>()
{
  return "fishros_cpp/msg/SystemStatus";
}

template<>
struct has_fixed_size<fishros_cpp::msg::SystemStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<fishros_cpp::msg::SystemStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<fishros_cpp::msg::SystemStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // FISHROS_CPP__MSG__DETAIL__SYSTEM_STATUS__TRAITS_HPP_
