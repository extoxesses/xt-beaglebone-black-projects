cmake_minimum_required(VERSION 2.8.3)
project(kuri_mbzirc_finder)
##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  gazebo_ros
  geometry_msgs
  laser_geometry
  pcl_conversions
  pcl_ros
  roscpp
  sensor_msgs
  std_msgs
  tf
  tf_conversions
#  cv_bridge
#  image_transport  
)
find_package(OpenCV REQUIRED)

###################################################
## Declare things to be passed to other projects ##
###################################################

catkin_package(
  CATKIN_DEPENDS
)

###########
## Build ##
###########
include_directories(include
  ${catkin_INCLUDE_DIRS}
)

add_library(cluster_analyzer
  src/${PROJECT_NAME}/cluster_analyzer.cpp
)

add_library(pannel_finder
  src/${PROJECT_NAME}/finder.cpp
)

add_library(laser_scan
  src/${PROJECT_NAME}/laser_scan.cpp
)

add_executable(finder_node
  src/${PROJECT_NAME}/main.cpp
)

## Specify libraries to link a library or executable target against
target_link_libraries(finder_node
  ${catkin_LIBRARIES}
  pannel_finder
)

target_link_libraries(laser_scan
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  cluster_analyzer
)

target_link_libraries(cluster_analyzer
  ${catkin_LIBRARIES}
)

target_link_libraries(pannel_finder
  ${catkin_LIBRARIES}
  laser_scan
  cluster_analyzer
)

#############
## Install ##
#############


#############
## Testing ##
#############
