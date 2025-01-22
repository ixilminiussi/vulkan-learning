# cmx/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(vulkan-learning CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")  
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

file(GLOB SOURCES *.cpp)

add_executable(test ${SOURCES})

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/.external/stb)
target_link_libraries(test PRIVATE assimp spdlog glfw vulkan dl pthread X11 Xxf86vm Xrandr Xi)
