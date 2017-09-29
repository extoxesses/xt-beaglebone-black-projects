#include <../include/usb_cam_reader.h>

#include <iostream>
#include <ros/ros.h>

using namespace std;

int main(int argc, char **argv) {
  ros::init(argc, argv, "cam_publisher");
  ros::NodeHandle nh;

  int idx = 1   ;

  bbb_roadtest::USBCamReader cr = bbb_roadtest::USBCamReader(nh, idx);
  cr.start(true);

  ros::spin();
  return 0;
} //main
