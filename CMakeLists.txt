cmake_minimum_required(VERSION 3.10)
project (ctello)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

find_package(spdlog REQUIRED)
find_package(OpenCV REQUIRED)

# CTello Shared Library =======================================================

add_library(ctello SHARED src/ctello.cpp)

target_include_directories(ctello PRIVATE include)
target_link_libraries(ctello PRIVATE spdlog::spdlog)

install(TARGETS ctello DESTINATION lib)
install(FILES include/ctello.h DESTINATION include)

# ctello_stream Command ==============================================================

add_executable(cv_video src/ctello_stream.cpp)

target_include_directories(cv_video PRIVATE include)
target_link_libraries(cv_video ctello)
target_link_libraries(cv_video ${OpenCV_LIBS})

