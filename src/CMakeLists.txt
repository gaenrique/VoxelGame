cmake_minimum_required(VERSION 3.8) 

add_executable("VoxelGame" VoxelGame.cpp "Renderer/VertexArray.cpp" "Renderer/GLError.h")

target_link_libraries("VoxelGame" glfw opengl32.lib glew32s.lib)


