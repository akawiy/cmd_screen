#include <opencv2/opencv.hpp>
#include "../../headers/convert.hpp"
#include "../../headers/utils.hpp"


void show_image(cv::Mat& image) {
    std::cout << "\x1b[H";  // Move cursor to top left
    std::cout << convert(image);
}

void show_image(const std::string& image_path) {
    cv::Mat image = cv::imread(image_path);
    std::cout << "\x1b[2J";  // Clear visible terminal space
    show_image(image);
}


void show_video(const std::string& video_path, const bool preload) {
    cv::VideoCapture video(video_path);
    const double fps = video.get(cv::CAP_PROP_FPS);
    cv::Mat frame;
    int frame_n = 0;
    std::cout << "\x1b[2J"; // Clear visible terminal space

    if (preload) {
        std::vector<std::string> frames{};

        while (true) {
            video >> frame;
            if (frame.empty()) {
                break;
            }
            std::string frame_str = convert(frame);
            frames.push_back(frame_str);

            std::cout << "\x1b[H";  // Move cursor to top left
            std::cout << frame_str;
        }

        const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

        while (true) {
            double elapsed_s = get_time_elapsed_s(start);

            // Skip frames if rendering isn't fast enough
            do {
                frame_n++;
            } while (elapsed_s * fps > frame_n);

            if (frame_n >= frames.size()) {
                return;
            }

            std::cout << "\x1b[H";  // Move cursor to top left
            std::cout << frames[frame_n];

            // Pause if rendering is too fast
            while (elapsed_s * fps < frame_n) {
                elapsed_s = get_time_elapsed_s(start);
            }
        }

        return;
    }

    const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    while (true) {
        double elapsed_s = get_time_elapsed_s(start);

        // Skip frames if rendering isn't fast enough
        do {
            video >> frame;
            if (frame.empty()) {
                return;
            }
            frame_n++;
        } while (elapsed_s * fps > frame_n);

        show_image(frame);

        // Pause if rendering is too fast
        while (elapsed_s * fps < frame_n) {
            elapsed_s = get_time_elapsed_s(start);
        }
    }
}


void show_camera(const int camera_index) {
    cv::VideoCapture camera(camera_index);

    std::cout << "\x1b[2J";  // Clear visible terminal space
    cv::Mat frame;

    while (true) {
        camera >> frame;
        if (frame.empty()) {
            return;
        }
        show_image(frame);
    }
}

void show_camera() {
    show_camera(0);
}
