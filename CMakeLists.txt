cmake_minimum_required(VERSION 3.25)
project(cpp_image_printer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(OpenCV_DIR "C:/tools/opencv/build")

find_package(OpenCV REQUIRED)

add_executable(cpp_image_printer print.cpp)

target_include_directories(cpp_image_printer PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(cpp_image_printer PRIVATE ${OpenCV_LIBS})
