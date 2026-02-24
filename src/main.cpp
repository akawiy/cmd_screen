#include "../headers/entries.hpp"


int main(const int argc, char* argv[]) {
    // Disable OpenCV debug info logging
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    const std::string mode = argv[1];
    if (mode == "img") {
        show_image(argv[2]);
    } else if (mode == "vid") {
        if (argc == 4) {
            const std::string option = argv[3];
            if (option == "preload") {
                show_video(argv[2], true);
            }
        } else {
            show_video(argv[2], false);
        }
    } else if (mode == "cam") {
        if (argc == 2) {
            show_camera();
        } else {
            show_camera(std::stoi(argv[2]));
        }
    }

    return 0;
}
