#include <../include/cam_subscriber.h>



namespace bbb_roadtest{

CamSubscriber::CamSubscriber(ros::NodeHandle& nh, std::string& properties_path){
  nh_ = nh;
  properties_path_ = properties_path;

  getProperties();

  image_transport::ImageTransport it(nh_);
  frame_sub_ = it.subscribe(sub_topic_, 1, &CamSubscriber::frameCallback, this);
  frame_pub_ = it.advertise(pub_topic_, 1);
}//constructor

CamSubscriber::~CamSubscriber(){}//destructor



// --- PRIVATE METHODS --- //

void CamSubscriber::getProperties(){
  cv::FileStorage cv_file_storage(properties_path_, cv::FileStorage::READ);
  if(!cv_file_storage.isOpened()){
    std::string error_msg = "[CamSubscriber] File \"" + properties_path_ + "\" not found!";
    throw std::invalid_argument(error_msg);
  }//if

  cv_file_storage["pub_topic"] >> pub_topic_;
  cv_file_storage["sub_topic"] >> sub_topic_;
  cv_file_storage["debug"] >> debug_mode_;

  cv_file_storage["alpha"] >> alpha_;
  cv_file_storage["beta"] >> beta_;

  cv_file_storage.release();
}//getProperties

void CamSubscriber::frameCallback(const sensor_msgs::ImageConstPtr& frame){
  try{
    last_frame_ = cv_bridge::toCvCopy(frame, "mono8")->image;
    last_frame_.convertTo(last_frame_, -1, alpha_, beta_);

    if(!last_frame_.empty()){
      sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", last_frame_).toImageMsg();
      frame_pub_.publish(msg);

      if(debug_mode_){
          displayFrame(last_frame_);
      }//if
    }//if
  }catch(cv_bridge::Exception& e){
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", frame->encoding.c_str());
  }//try-catch
}//frameCallback


void CamSubscriber::displayFrame(const cv::Mat& frame){
  cv::imshow("Frame grabber", frame);
  cv::waitKey(0);
}//dislayFrame

}//namespace
