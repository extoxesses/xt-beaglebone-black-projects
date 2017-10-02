#include <../include/cam_subscriber.h>



namespace bbb_roadtest{

CamSubscriber::CamSubscriber(ros::NodeHandle& nh, std::string& sub_topic, std::string& pub_topic, bool debug){
  nh_ = nh;
  sub_topic_ = sub_topic;
  pub_topic_ = pub_topic;
  debug_mode_ = debug;

  image_transport::ImageTransport it(nh_);
  frame_sub_ = it.subscribe(sub_topic_, 1, &CamSubscriber::frameCallback, this);
  frame_pub_ = it.advertise(pub_topic_, 1);
}//constructor

CamSubscriber::~CamSubscriber(){}//destructor



// --- PRIVATE METHODS --- //

void CamSubscriber::frameCallback(const sensor_msgs::ImageConstPtr& frame){
  try{
    // last_frame_ = cv_bridge::toCvCopy(frame, sensor_msgs::image_encodings::MONO16)->image;
    // last_frame_ = cv_bridge::toCvCopy(frame, "bgr8")->image;
    last_frame_ = cv_bridge::toCvCopy(frame, "mono8")->image;
    last_frame_.convertTo(last_frame_, -1, 10, -200);

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
