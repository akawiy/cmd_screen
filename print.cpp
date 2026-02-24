// Made on 20.02.2026 and 21.02.2026

#include <iostream>
#include <windows.h>
#include <opencv2/opencv.hpp>


cv::Size get_terminal_size() {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);

    const cv::Size terminal_size {
        buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1,
        buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1,
    };
    return terminal_size;
}


cv::Mat load_image(const std::string& path) {
    constexpr double k = 0.5057;  // Character aspect ratio

    // Loading image and getting its parameters
    cv::Mat image = cv::imread(path, cv::IMREAD_GRAYSCALE);
    const cv::Size image_size {
        image.cols,
        image.rows,
    };
    const double image_aspect_ratio = static_cast<double>(image_size.width) / image_size.height / k;

    // Resizing image to fit into the command prompt
    const cv::Size terminal_size = get_terminal_size();
    const cv::Size new_image_size {
        terminal_size.width,
        static_cast<int>(terminal_size.width / image_aspect_ratio),
    };
    cv::resize(image, image, new_image_size, 0, 0, cv::INTER_LINEAR);

    return image;
}


std::string to_chars(const cv::Mat& image) {
    const cv::Size image_size = image.size();

    // Converting each pixel into character by its lightness
    const std::string palette = " .,-~:;=!*#$@";
    std::string chars;
    for (int i = 0; i < image_size.height; i++) {
        for (int j = 0; j < image_size.width; j++) {
            const uchar pixel = image.at<uchar>(i, j);
            chars += palette.at(pixel * palette.length() / 256);
        }
    }

    return chars;
}


int main(const int argc, char* argv[]) {
    std::string image_path;
    if (argc == 1) {
        std::cout << "Image path > ";
        std::cin >> image_path;
    } else {
        image_path = argv[1];
    }

    const cv::Mat& image = load_image(image_path);
    const std::string chars = to_chars(image);
    std::cout << chars;

    if (argc == 1) {
        // Wait for the user to press Enter
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}
