cmake_minimum_required (VERSION 3.22)

project("AsioExamples")

set(CMAKE_CXX_STANDARD 20)
# ...
find_package(asio REQUIRED)
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIR})
link_libraries(asio::asio boost::boost)

add_subdirectory(Example1)
add_subdirectory(port_scanner)
