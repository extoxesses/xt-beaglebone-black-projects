#include <../include/cam_subscriber.h>

#include <iostream>
#include <fstream>

using namespace std;

/**
 * @brief getValuesFromFile - This function read input data from an xml configuration file.
 * @param prop_path - Configuration file path
 * @param topic     - Topic published
 * @param cam_idx   - Index of wanted camera
 * @param debug     - Flag. If true, debug gui will be shown
 */
/*void getValuesFromFile(const string& prop_path, string& topic, int& cam_idx, bool& debug){
  cv::FileStorage cv_file_storage(prop_path, cv::FileStorage::READ);
  if(!cv_file_storage.isOpened()){
    string error_msg = "[cam_publisher] File \"" + prop_path + "\" not found!";
    throw invalid_argument(error_msg);
  }//if

  cv_file_storage["topic"] >> topic;
  cv_file_storage["cam_idx"] >> cam_idx;
  cv_file_storage["debug"] >> debug;

  cv_file_storage.release();
}//getValuesFromFile*/



int main(int argc, char **argv){
  ros::init(argc, argv, "cam_subscriber");
  ros::NodeHandle nh;

  /*if(argc != 2){
    ROS_ERROR("Input file path measing!");
    return 1;
  }//if*/

  string sub_topic = "/bbb_roadtest/cam_publisher";
  string pub_topic = "/bbb_roadtest/cam_subscriber";
  bool debug = false;

  bbb_roadtest::CamSubscriber sub = bbb_roadtest::CamSubscriber(nh, sub_topic, pub_topic, debug);

  ros::spin();
  return 0;
} //main
