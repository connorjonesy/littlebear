cmake_minimum_required(VERSION 3.16)
project(littlebear)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(littlebear ${SOURCES})

target_link_libraries(littlebear PRIVATE SFML::Graphics SFML::Window SFML::System)
