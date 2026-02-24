cmake_minimum_required(VERSION 3.25)
project(cmd_screen)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(OpenCV_DIR "C:/tools/opencv/build")

find_package(OpenCV REQUIRED)

add_executable(
        cmd_screen src/main.cpp
        src/lib/convert.cpp headers/convert.hpp
        src/lib/entries.cpp headers/entries.hpp
        src/lib/utils.cpp headers/utils.hpp
)

target_include_directories(cmd_screen PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(cmd_screen PRIVATE ${OpenCV_LIBS})
