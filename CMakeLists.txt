cmake_minimum_required(VERSION 3.6)
project(facetracker)

set(CMAKE_CXX_STANDARD 14)

# OpenBLAS
include_directories(/usr/local/Cellar/openblas/0.2.20/include)
link_directories(/usr/local/Cellar/openblas/0.2.20/lib)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# AUX_SOURCE_DIRECTORY(mtcnn MTCNN_SRCS)
set(SOURCE_FILES main.cpp util/ElapsedTimer.cpp util/ElapsedTimer.hpp)
add_executable(tracker ${SOURCE_FILES})

find_package(dlib)

target_link_libraries(tracker ${OpenCV_LIBS})
# target_link_libraries(tracker openblas)
target_link_libraries(tracker dlib::dlib)