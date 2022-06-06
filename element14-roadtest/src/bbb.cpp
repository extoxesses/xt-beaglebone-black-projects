#include <../include/cam_subscriber.h>

#include <iostream>
#include <fstream>

using namespace std;



int main(int argc, char **argv){
  ros::init(argc, argv, "cam_subscriber");
  ros::NodeHandle nh;

  string prop_path;
  if(argc != 2){
    ROS_WARN("Input file path missing! Default path is used!");
    prop_path = "./src/BBBRoadtest/resources/bbb_properties.xml";
  }else{
    prop_path = argv[1];
  }//if-else

  bbb_roadtest::CamSubscriber subscriber = bbb_roadtest::CamSubscriber(nh, prop_path);

  ros::spin();
  return 0;
} //main
