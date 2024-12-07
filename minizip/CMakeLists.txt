cmake_minimum_required (VERSION 3.22)

project("zip_utility")

set(CMAKE_CXX_STANDARD 20)

find_package(miniz REQUIRED)
find_package(argparse REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} miniz::miniz argparse::argparse)
