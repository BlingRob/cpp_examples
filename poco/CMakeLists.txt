cmake_minimum_required (VERSION 3.22)

project("PocoExample")

set(CMAKE_CXX_STANDARD 20)
# ...
find_package(poco REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${poco_LIBS} ${poco_LIBS_DEBUG} ${poco_LIBRARIES_DEBUG})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${poco_INCLUDE_DIRS_DEBUG})

