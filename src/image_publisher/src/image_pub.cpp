#include "image_publisher/image_pub.hpp"
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <memory>
#include <chrono>
#include <opencv2/core/mat.hpp>
#include <rclcpp/context.hpp>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <std_msgs/msg/detail/header__struct.hpp>

ImagePublisherNode::ImagePublisherNode():Node("image_publisher"){
    this->declare_parameter<double>("frequency",10.0);
    this->get_parameter("frequency",freq);
    RCLCPP_INFO(this->get_logger(),"Frequency:%.2f Hz",freq);
    publisher_=image_transport::create_publisher(this, "image_raw");
    init_camera();
}

void ImagePublisherNode::init_camera(){
    this->declare_parameter<int>("camera_id",0);
    this->get_parameter("camera_id",camera_id);
    cap_.open(camera_id);

    if(!cap_.isOpened()){
        RCLCPP_ERROR(this->get_logger(),"camera cannot opened!");
        rclcpp::shutdown();
        return;
    }

    timer_=this->create_wall_timer(
        std::chrono::milliseconds(static_cast<int>(1000/ImagePublisherNode::freq)),
        std::bind(&ImagePublisherNode::timer_callback,this)
    );
}

void ImagePublisherNode::timer_callback(){
    cv::Mat frame;
    cap_ >> frame;

    if(frame.empty()) return;


    std_msgs::msg::Header header;
    header.stamp = this->get_clock()->now();

    auto msg = cv_bridge::CvImage(header,"bgr8",frame).toImageMsg();
    publisher_.publish(msg);
}


int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImagePublisherNode>());
    rclcpp::shutdown();
    return 0;
}