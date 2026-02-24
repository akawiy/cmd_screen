#pragma once

#include <opencv2/opencv.hpp>


void show_image(cv::Mat& image);

void show_image(const std::string& image_path);

void show_video(const std::string& video_path, bool preload);

void show_camera(int camera_index);

void show_camera();
