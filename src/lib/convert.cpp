#include <opencv2/opencv.hpp>
#include "../../headers/utils.hpp"


const std::string CHARS = " .,-~:;=!*#$@";


// Basic image-to-characters conversion (centered, fast)
std::string convert_char(cv::Mat& image) {
    resize_image(image);
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);  // Convert to grayscale

    const cv::Size terminal_size = get_terminal_size();
    std::string result;

    result += center(image, terminal_size, true, false);
    for (int i = 0; i < image.rows; i++) {
        result += center(image, terminal_size, false, false);

        for (int j = 0; j < image.cols; j++) {
            const uchar pixel_lightness = image.at<uchar>(i, j);

            // Add character by pixel lightness
            result += CHARS.at(pixel_lightness * CHARS.length() / 256);
        }

        result += center(image, terminal_size, false, true);
    }
    result += center(image, terminal_size, true, true);

    return result;
}


// Clean ANSI 24-bit Truecolor bitmap/raster image conversion (centered, recommended)
std::string convert_bitmap(cv::Mat& image) {
    resize_image(image);

    const cv::Size terminal_size = get_terminal_size();
    std::string result;

    result += center(image, terminal_size, true, false);
    for (int i = 0; i < image.rows; i++) {
        result += center(image, terminal_size, false, false);

        for (int j = 0; j < image.cols; j++) {
            result += ansi_truecolor(image.at<cv::Vec3b>(i, j), true);
            result += " ";
        }

        result += "\033[0m";  // Reset color
        result += center(image, terminal_size, false, true);
    }
    result += center(image, terminal_size, true, true);

    return result;
}


// Current image conversion method (edit manually)
std::string convert(cv::Mat& image) {
    return convert_bitmap(image);
}
