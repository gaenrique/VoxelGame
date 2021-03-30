cmake_minimum_required(VERSION 3.8) 

add_executable("VoxelGame" VoxelGame.cpp)

target_link_libraries("VoxelGame" glfw opengl32.lib glew32s.lib)



