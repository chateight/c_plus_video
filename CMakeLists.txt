cmake_minimum_required(VERSION 3.1)
project (test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(cv_video ctello_stream.cpp)
target_link_libraries(cv_video ${OpenCV_LIBS})

