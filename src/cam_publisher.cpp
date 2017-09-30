#include <../include/usb_cam_reader.h>

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
void getValuesFromFile(const string& prop_path, string& topic, int& cam_idx, bool& debug){
  cv::FileStorage cv_file_storage(prop_path, cv::FileStorage::READ);
  if(!cv_file_storage.isOpened()){
    string error_msg = "[cam_publisher] File \"" + prop_path + "\" not found!";
    throw invalid_argument(error_msg);
  }//if

  cv_file_storage["topic"] >> topic;
  cv_file_storage["cam_idx"] >> cam_idx;
  cv_file_storage["debug"] >> debug;

  cv_file_storage.release();
}//getValuesFromFile



int main(int argc, char **argv){
  ros::init(argc, argv, "cam_publisher");
  ros::NodeHandle nh;

  if(argc != 2){
    ROS_ERROR("Input file path measing!");
    return 1;
  }//if

  string prop_path = argv[1];
  string topic;
  int cam_idx;
  bool show;

  getValuesFromFile(prop_path, topic, cam_idx, show);

  bbb_roadtest::USBCamReader cr = bbb_roadtest::USBCamReader(nh, cam_idx, topic);
  cr.start(false);

  ros::spin();
  return 0;
} //main
