cmake_minimum_required(VERSION 3.5)
project(fishros_cpp)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/SystemStatus.msg"
  DEPENDENCIES builtin_interfaces
)


## topicPub
add_executable(topicPub src/topicPub.cpp)
target_include_directories(topicPub PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
        topicPub
        "rclcpp" "std_msgs"
)

## topicSub
add_executable(topicSub src/topicSub.cpp)
target_include_directories(topicSub PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  topicSub
  "rclcpp" "std_msgs"
)

## turtle_circle
add_executable(turtle_circle src/turtle_circle.cpp)
target_include_directories(turtle_circle PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
        turtle_circle
        "rclcpp" "geometry_msgs" "turtlesim"
)

## turtle_control
add_executable(turtle_control src/turtle_control.cpp)
target_include_directories(turtle_control PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
        turtle_control
        "rclcpp" "geometry_msgs" "turtlesim"
)

## system_status_pub
add_executable(system_status_pub src/system_status_pub.cpp)
target_include_directories(system_status_pub PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
        system_status_pub
        "rclcpp"
)


install(TARGETS topicPub topicSub turtle_circle turtle_control system_status_pub
  DESTINATION lib/${PROJECT_NAME})

ament_package()