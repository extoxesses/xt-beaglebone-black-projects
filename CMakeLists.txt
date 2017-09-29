cmake_minimum_required(VERSION 2.8.3)
project(bbb_roadtest)
include_directories(./include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  cv_bridge
#  actionlib
#  actionlib_msgs
#  gazebo_ros
#  geometry_msgs
#  laser_geometry
#  pcl_conversions
#  pcl_ros
#  roscpp
#  sensor_msgs
#  std_msgs
#  tf
#  tf_conversions
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

add_library(cam_reader
  ./src/usb_cam_reader.cpp
)

add_executable(cam_publisher
  ./src/cam_publisher.cpp
)



target_link_libraries(cam_reader
   ${catkin_LIBRARIES}
)

target_link_libraries(cam_publisher
  cam_reader
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############


#############
## Testing ##
#############
