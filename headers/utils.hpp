#pragma once

#include <opencv2/opencv.hpp>


cv::Size get_terminal_size();

cv::Size get_target_image_size(double image_aspect_ratio);

void resize_image(cv::Mat& image);

std::string center(const cv::Mat& image, const cv::Size& terminal_size, bool axis, bool side);

std::string ansi_truecolor(const cv::Vec3b& color_bgr, bool is_bg);

double get_time_elapsed_s(const std::chrono::steady_clock::time_point& start);
