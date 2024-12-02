cmake_minimum_required(VERSION 3.14)
project("ROS2_demo")

include("/opt/ros/scripts/cmake/colcon.cmake")

# only for clion highlighting and analysis
colcon_add_subdirectories(
        BUILD_BASE "${PROJECT_SOURCE_DIR}/build"
        BASE_PATHS "${PROJECT_SOURCE_DIR}/src/"
        --packages-select helloworld_cpp
)