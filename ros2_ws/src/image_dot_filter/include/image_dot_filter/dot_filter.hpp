#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class DotFilter {
public:
    DotFilter(int block_size = 32);

    cv::Mat apply(const cv::Mat& input_img);

private:
    int block_size_;
    std::vector<cv::Scalar> palette_;

    // 色をパレット内に量子化する
    cv::Scalar findNearestColor(const cv::Scalar& color);
};
