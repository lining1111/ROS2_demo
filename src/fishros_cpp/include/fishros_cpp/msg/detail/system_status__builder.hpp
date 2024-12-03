// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from fishros_cpp:msg/SystemStatus.idl
// generated code does not contain a copyright notice

#ifndef FISHROS_CPP__MSG__DETAIL__SYSTEM_STATUS__BUILDER_HPP_
#define FISHROS_CPP__MSG__DETAIL__SYSTEM_STATUS__BUILDER_HPP_

#include "fishros_cpp/msg/detail/system_status__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace fishros_cpp
{

namespace msg
{

namespace builder
{

class Init_SystemStatus_net_recv
{
public:
  explicit Init_SystemStatus_net_recv(::fishros_cpp::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  ::fishros_cpp::msg::SystemStatus net_recv(::fishros_cpp::msg::SystemStatus::_net_recv_type arg)
  {
    msg_.net_recv = std::move(arg);
    return std::move(msg_);
  }

private:
  ::fishros_cpp::msg::SystemStatus msg_;
};

class Init_SystemStatus_net_sent
{
public:
  explicit Init_SystemStatus_net_sent(::fishros_cpp::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_net_recv net_sent(::fishros_cpp::msg::SystemStatus::_net_sent_type arg)
  {
    msg_.net_sent = std::move(arg);
    return Init_SystemStatus_net_recv(msg_);
  }

private:
  ::fishros_cpp::msg::SystemStatus msg_;
};

class Init_SystemStatus_memory_available
{
public:
  explicit Init_SystemStatus_memory_available(::fishros_cpp::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_net_sent memory_available(::fishros_cpp::msg::SystemStatus::_memory_available_type arg)
  {
    msg_.memory_available = std::move(arg);
    return Init_SystemStatus_net_sent(msg_);
  }

private:
  ::fishros_cpp::msg::SystemStatus msg_;
};

class Init_SystemStatus_memory_total
{
public:
  explicit Init_SystemStatus_memory_total(::fishros_cpp::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_memory_available memory_total(::fishros_cpp::msg::SystemStatus::_memory_total_type arg)
  {
    msg_.memory_total = std::move(arg);
    return Init_SystemStatus_memory_available(msg_);
  }

private:
  ::fishros_cpp::msg::SystemStatus msg_;
};

class Init_SystemStatus_memory_percent
{
public:
  explicit Init_SystemStatus_memory_percent(::fishros_cpp::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_memory_total memory_percent(::fishros_cpp::msg::SystemStatus::_memory_percent_type arg)
  {
    msg_.memory_percent = std::move(arg);
    return Init_SystemStatus_memory_total(msg_);
  }

private:
  ::fishros_cpp::msg::SystemStatus msg_;
};

class Init_SystemStatus_cpu_percent
{
public:
  explicit Init_SystemStatus_cpu_percent(::fishros_cpp::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_memory_percent cpu_percent(::fishros_cpp::msg::SystemStatus::_cpu_percent_type arg)
  {
    msg_.cpu_percent = std::move(arg);
    return Init_SystemStatus_memory_percent(msg_);
  }

private:
  ::fishros_cpp::msg::SystemStatus msg_;
};

class Init_SystemStatus_host
{
public:
  explicit Init_SystemStatus_host(::fishros_cpp::msg::SystemStatus & msg)
  : msg_(msg)
  {}
  Init_SystemStatus_cpu_percent host(::fishros_cpp::msg::SystemStatus::_host_type arg)
  {
    msg_.host = std::move(arg);
    return Init_SystemStatus_cpu_percent(msg_);
  }

private:
  ::fishros_cpp::msg::SystemStatus msg_;
};

class Init_SystemStatus_stamp
{
public:
  Init_SystemStatus_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SystemStatus_host stamp(::fishros_cpp::msg::SystemStatus::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_SystemStatus_host(msg_);
  }

private:
  ::fishros_cpp::msg::SystemStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::fishros_cpp::msg::SystemStatus>()
{
  return fishros_cpp::msg::builder::Init_SystemStatus_stamp();
}

}  // namespace fishros_cpp

#endif  // FISHROS_CPP__MSG__DETAIL__SYSTEM_STATUS__BUILDER_HPP_
