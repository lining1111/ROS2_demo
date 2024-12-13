#!/bin/bash
mv CMakeLists.txt CMakeLists.txt.bak
output=`colcon build`
echo ${output}
mv CMakeLists.txt.bak CMakeLists.txt
