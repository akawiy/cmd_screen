#include <windows.h>
#include <opencv2/opencv.hpp>


constexpr double CHARACTER_ASPECT_RATIO = 0.5;


cv::Size get_terminal_size() {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);

    const cv::Size terminal_size {
        buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1,
        buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1,
    };
    return terminal_size;
}


cv::Size get_target_image_size(const double image_aspect_ratio) {
    const cv::Size terminal_size = get_terminal_size();
    const cv::Size target_image_size {
        std::min(terminal_size.width, static_cast<int>(terminal_size.height * image_aspect_ratio)),
        std::min(terminal_size.height, static_cast<int>(terminal_size.width / image_aspect_ratio)),
    };
    return target_image_size;
}


void resize_image(cv::Mat& image) {
    const double image_aspect_ratio = static_cast<double>(image.cols) / image.rows / CHARACTER_ASPECT_RATIO;
    const cv::Size new_image_size = get_target_image_size(image_aspect_ratio);
    cv::resize(image, image, new_image_size, 0, 0, cv::INTER_LINEAR);
}


std::string center(const cv::Mat& image, const cv::Size& terminal_size, const bool axis, const bool side) {
    std::string result;

    if (axis) {
        // Center image on Y axis ([side == false] is top, [side == true] is bottom)
        const int n = std::floor((terminal_size.height - image.rows) / 2. + .5 * side);
        if (image.rows < terminal_size.height) {
            for (int i = 0; i < n * terminal_size.width; i++) {
                result += " ";
            }
        }
    } else {
        // Center image on X axis ([side == false] is left, [side == true] is right)
        const int n = std::floor((terminal_size.width - image.cols) / 2. + .5 * side);
        if (image.cols < terminal_size.width) {
            for (int i = 0; i < n; i++) {
                result += " ";
            }
        }
    }

    return result;
}


std::string ansi_truecolor(const cv::Vec3b& color_bgr, const bool is_bg) {
    std::string result;

    result += "\033[";
    if (is_bg) {
        result += "48;2;";  // Background
    } else {
        result += "38;2;";  // Text
    }
    result += std::to_string(color_bgr[2]);
    result += ";";
    result += std::to_string(color_bgr[1]);
    result += ";";
    result += std::to_string(color_bgr[0]);
    result += "m";

    return result;
}


double get_time_elapsed_s(const std::chrono::steady_clock::time_point& start) {
    const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    const std::chrono::microseconds difference = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
    const double elapsed_s = static_cast<double>(difference.count()) / 1000000.;
    return elapsed_s;
}
