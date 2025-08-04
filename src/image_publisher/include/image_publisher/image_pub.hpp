#ifndef IMAGE_PUB_HPP_
#define IMAGE_PUB_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <opencv2/opencv.hpp>

class ImagePublisherNode : public rclcpp::Node {
public:
  ImagePublisherNode();

private:
  void init_camera();
  void timer_callback();
  double freq=10.0;//Hz
  int camera_id;
  image_transport::Publisher publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  cv::VideoCapture cap_;
};

#endif