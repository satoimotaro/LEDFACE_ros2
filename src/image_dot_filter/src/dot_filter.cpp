#include "image_dot_filter/dot_filter.hpp"
#include <algorithm>
#include <cfloat>  // for DBL_MAX

DotFilter::DotFilter(int block_size) : block_size_(block_size) {
    // 4色のカラーパレット（BGR順）
    palette_ = {
        cv::Scalar(0, 0, 0),       // 黒
        cv::Scalar(0, 0, 255),     // 赤
        cv::Scalar(0, 255, 0),     // 緑
        cv::Scalar(0, 255, 255),   // 黄
    };
}

cv::Mat DotFilter::apply(const cv::Mat& input_img) {
    // 入力画像の明るさを標準化
    double target_brightness = 128.0;
    cv::Mat gray;
    cv::cvtColor(input_img, gray, cv::COLOR_BGR2GRAY);
    double current_brightness = cv::mean(gray)[0];
    double scale = target_brightness / (current_brightness + 1e-5);

    cv::Mat adjusted_img;
    input_img.convertTo(adjusted_img, -1, scale, 0);

    // ドット画像生成
    cv::Mat dot_img = cv::Mat::zeros(adjusted_img.size(), adjusted_img.type());

    for (int y = 0; y < adjusted_img.rows; y += block_size_) {
        for (int x = 0; x < adjusted_img.cols; x += block_size_) {
            int bw = std::min(block_size_, adjusted_img.cols - x);
            int bh = std::min(block_size_, adjusted_img.rows - y);

            cv::Rect roi(x, y, bw, bh);
            cv::Mat block = adjusted_img(roi);

            cv::Scalar avg_color = cv::mean(block);
            cv::Scalar quantized = findNearestColor(avg_color);

            cv::Point center(x + bw / 2, y + bh / 2);
            int radius = std::min(bw, bh) / 2;

            cv::circle(dot_img, center, radius, quantized, -1);
        }
    }

    return dot_img;
}

cv::Scalar DotFilter::findNearestColor(const cv::Scalar& color) {
    double min_dist = DBL_MAX;
    cv::Scalar best_color = palette_[0];

    for (const auto& c : palette_) {
        double dist = 0.0;
        for (int i = 0; i < 3; ++i) {
            double d = color[i] - c[i];
            dist += d * d;
        }

        if (dist < min_dist) {
            min_dist = dist;
            best_color = c;
        }
    }

    return best_color;
}
