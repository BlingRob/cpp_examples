cmake_minimum_required (VERSION 3.22)

project("OpenCVExample")

set(CMAKE_CXX_STANDARD 20)
# ...
find_package(OpenCV REQUIRED core CONFIG)

# include_directories(${OrbitProfiler_INCLUDE_DIRS})
# link_directories(${OrbitProfiler_LIBRARY_DIR})
# link_libraries(asio::asio boost::boost)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
