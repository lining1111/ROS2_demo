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
find_package(rclcpp_action REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(system_status_interface REQUIRED)
find_package(face_recognition REQUIRED)
find_package(robot_control_interfaces REQUIRED)

#### --------话题
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
add_executable(system_status_pub src/system_status_pub.cpp
        systemStatus/systemStatus.cpp)
target_include_directories(system_status_pub PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
        system_status_pub
        "rclcpp"
        "system_status_interface"
)

## system_status_sub
add_executable(system_status_sub src/system_status_sub.cpp)
target_include_directories(system_status_sub PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
        system_status_sub
        "rclcpp"
        "system_status_interface"
)

#### --------服务

## face_recognition_server
add_executable(face_recognition_server src/face_recognition_server.cpp)
target_include_directories(face_recognition_server PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
        face_recognition_server
        "rclcpp"
        "face_recognition" "cv_bridge"
)

## face_recognition_client
add_executable(face_recognition_client src/face_recognition_client.cpp)
target_include_directories(face_recognition_client PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
        face_recognition_client
        "rclcpp"
        "face_recognition" "cv_bridge"
)

#### --------参数

## example_parameters
add_executable(example_parameters src/example_parameters.cpp)
target_include_directories(example_parameters PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
        example_parameters
        "rclcpp"
)


#### --------动作
add_executable(action_robot src/action_robot.cpp src/robot.cpp)
target_include_directories(action_robot PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
        action_robot
        "rclcpp"
        "rclcpp_action"
        "robot_control_interfaces"
)

add_executable(action_control src/action_control.cpp )
target_include_directories(action_control PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
        action_control
        "rclcpp"
        "rclcpp_action"
        "robot_control_interfaces"
)


install(TARGETS topicPub topicSub turtle_circle turtle_control system_status_pub system_status_sub
        face_recognition_server face_recognition_client
        example_parameters
        action_robot action_control
  DESTINATION lib/${PROJECT_NAME})

ament_package()