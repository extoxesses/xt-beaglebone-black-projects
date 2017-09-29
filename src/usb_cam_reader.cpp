#include <../include/usb_cam_reader.h>

#include <sensor_msgs/Image.h>
#include <camera_info_manager/camera_info_manager.h>


namespace bbb_roadtest{

USBCamReader::USBCamReader(ros::NodeHandle& nh, int cam_idx, std::string& topic){
  nh_ = nh;
  cam_idx_ = cam_idx;
  frame_pub_ = nh_.advertise<sensor_msgs::Image>(topic, 1);
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
    cv::namedWindow("Video", 1);
  }//if show

  while(true){ // cosa da sitemare... così non può andare bene...
    cv::Mat frame;
    v_cap >> frame;
    publish(frame);

    if(show){
      displayFrame(frame);
    }//if
  }//while
}//start

/*******************
 * PRIVATE METHODS *
 *******************/
void USBCamReader::displayFrame(cv::Mat& frame){
  cv::imshow("Video", frame);
  cv::waitKey(0);
}//dislayFrame

void USBCamReader::publish(cv::Mat& frame){
    /*cv_bridge::CvImage out_msg;
    //out_msg.header   = frame->header; // Same timestamp and tf frame as input image
    out_msg.encoding = sensor_msgs::image_encodings::TYPE_32FC1; // Or whatever
    out_msg.image    = frame; // Your cv::Mat

    frame_pub_.publish(out_msg.toImageMsg());*/

  //image_transport::ImageTransport transport;
  image_transport::CameraPublisher image_pub;
  camera_info_manager::CameraInfoManager info_mgr(nh_, "test");

  ros::Time time = ros::Time::now();

  // convert OpenCV image to ROS message
  cv_bridge::CvImage cvi;
  cvi.header.stamp = time;
  cvi.header.frame_id = "image";
  cvi.encoding = "bgr8";
  cvi.image = frame;

  // get camera parameters
  sensor_msgs::CameraInfo info = info_mgr.getCameraInfo();
  info.header.stamp = cvi.header.stamp;
  info.header.frame_id = cvi.header.frame_id; // whatever it is called
  info.width = frame.cols;
  info.height = frame.rows;

  sensor_msgs::Image im;
  cvi.toImageMsg(im);
  image_pub.publish(im, info);

  //frame_pub_.publish(frame.toImageMsg());

  // TODO - guardare image_transport::Publish class o metodo, quel cazzo che è...
}//publish


}//namespace
