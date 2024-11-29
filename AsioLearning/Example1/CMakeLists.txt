cmake_minimum_required (VERSION 3.22)

project("Example1")

add_executable(example1 main.cpp)

# target_link_libraries (${CMAKE_PROJECT_NAME} asio::asio boost::boost)
# ...
# target_link_libraries(${CMAKE_PROJECT_NAME} asio::asio)