#include <../include/usb_cam_reader.h>

namespace bbb_roadtest{

USBCamReader::USBCamReader(ros::NodeHandle& nh, int cam_idx){
  nh_ = nh;
  cam_idx_ = cam_idx;
}//constructor

USBCamReader::~USBCamReader(){
}//destructor

void USBCamReader::start(bool show){
  cv::VideoCapture v_cap(cam_idx_);
  if(!v_cap.isOpened()){
    // rise an exception
    return;
  }//if

  if(show){
    cv::Mat frame;
    v_cap >> frame;
    displayFrame(frame);
  }//if

}//start



/*******************
 * PRIVATE METHODS *
 *******************/
void USBCamReader::displayFrame(cv::Mat& frame){
  cv::namedWindow("Video", 1);
  for(;;){
    cv::imshow("Video", frame);
    cv::waitKey(0);
    //if(cv::waitKey(30) >= 0){
    //    break;
   //}//if
}//for
}//dislayFrame

}//namespace
