/*
 * Copyright (c) 2010, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BBB_USB_CAM_READER
#define BBB_USB_CAM_READER

#include <string>

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace bbb_roadtest{
class USBCamReader{

public:
  /**
   * @brief USBCamReader - Default constructor
   * @param nh      - ROS node handle
   * @param cam_idx - Camera index
   * @param topic   - Publishing topic
   */
  USBCamReader(ros::NodeHandle& nh, int cam_idx, std::string& topic);
  /**
   * Default descrtuctor
   */
  ~USBCamReader();

  /**
   * @brief start - This method allow to the node to start to publish the camera stream
   * @param show - Flag, default equal to false. If true, a debug gui is shown
   */
  void start(bool show = false);

  // Getter methods
  int getCamIndex();
  void getTopic(std::string& topic);

private:
  ros::NodeHandle nh_;
  int cam_idx_;
  std::string topic_;
  image_transport::Publisher frame_pub_;

  /**
   * @brief displayFrame - This method allows to show a gui to see frames readed from the camera
   * @param frame - Readed frame
   */
  void displayFrame(const cv::Mat& frame);

};//class USBCamReader
}//namespace bbb_roadtest

#endif
