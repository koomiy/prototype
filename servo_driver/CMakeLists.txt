cmake_minimum_required(VERSION 3.0.2)
project(servo_driver)

add_definitions(-std=c++11 -O3)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

link_directories()

add_executable(servo_driver_node
  src/main.cpp
  src/servo_driver.cpp
  src/Adafruit_ServoDriver.cpp
)

target_link_libraries(servo_driver_node
  ${catkin_LIBRARIES}
)
