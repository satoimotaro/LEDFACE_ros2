#include <rclcpp/rclcpp.hpp>
#include <image_transport/image_transport.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>

#include "image_dot_filter/dot_filter.hpp"

class ImageDotFilterNode : public rclcpp::Node {
public:
  ImageDotFilterNode() : Node("image_dot_filter") {
    using std::placeholders::_1;

    filter_ = std::make_shared<DotFilter>();

    // サブスクライバ
    sub_ = image_transport::create_subscription(
      this, "image_raw",
      std::bind(&ImageDotFilterNode::image_callback, this, _1),
      "raw"
    );

    // パブリッシャ
    pub_ = image_transport::create_publisher(this, "image_dot");
  }

private:
  void image_callback(const sensor_msgs::msg::Image::ConstSharedPtr& msg) {
    // OpenCV に変換
    cv_bridge::CvImagePtr cv_ptr;
    try {
      cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    } catch (cv_bridge::Exception& e) {
      RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
      return;
    }

    // 画像処理
    cv::Mat filtered_img = filter_->apply(cv_ptr->image);

    // パブリッシュ
    auto out_msg = cv_bridge::CvImage(msg->header, "bgr8", filtered_img).toImageMsg();
    pub_.publish(out_msg);
  }

  image_transport::Subscriber sub_;
  image_transport::Publisher pub_;
  std::shared_ptr<DotFilter> filter_;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ImageDotFilterNode>());
  rclcpp::shutdown();
  return 0;
}
