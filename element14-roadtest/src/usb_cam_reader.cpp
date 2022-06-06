#include <../include/usb_cam_reader.h>

#include <sensor_msgs/Image.h>
#include <camera_info_manager/camera_info_manager.h>


namespace bbb_roadtest{

USBCamReader::USBCamReader(ros::NodeHandle& nh, int cam_idx, std::string& topic){
  nh_ = nh;
  cam_idx_ = cam_idx;
  topic_ = topic;

  image_transport::ImageTransport it(nh_);
  frame_pub_ = it.advertise(topic_, 1);
}//constructor

USBCamReader::~USBCamReader(){}//destructor

void USBCamReader::start(bool show){
  cv::VideoCapture v_cap(cam_idx_);
  if(!v_cap.isOpened()){
    // rise an exception
    return;
  }//if

  if(show){
    cv::namedWindow("Video", 1);
  }//if show


  while(nh_.ok()){
    cv::Mat frame;
    v_cap >> frame;

    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
    if(!frame.empty()){
      frame_pub_.publish(msg);
    }//if

    if(show){
      displayFrame(frame);
    }//if
  }//while
}//start

int USBCamReader::getCamIndex(){
  return cam_idx_;
}//getCamIndex

void USBCamReader::getTopic(std::string& topic){
  topic = topic_;
}//getTopic


// --- PRIVATE METHODS ---//


void USBCamReader::displayFrame(const cv::Mat& frame){
  cv::imshow("Video", frame);
  cv::waitKey(0);
}//dislayFrame

}//namespace
