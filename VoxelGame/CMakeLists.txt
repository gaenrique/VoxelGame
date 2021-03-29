cmake_minimum_required(VERSION 3.8)

add_executable("VoxelGame" VoxelGame.cpp)

# Link GLFW
target_link_libraries(VoxelGame glfw)

find_package(OpenGL REQUIRED)

target_link_libraries("VoxelGame" OpenGL::GL)