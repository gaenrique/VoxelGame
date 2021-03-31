# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("VoxelGame")

add_compile_definitions(GLEW_STATIC)
add_compile_definitions(DEBUG)
add_compile_definitions(STB_IMAGE_IMPLEMENTATION)

add_subdirectory("Dependencies/glfw")

# Linking to libraries and adding include directory for GLEW
include_directories("Dependencies/glew/include")
link_directories("Dependencies/glew/lib/Release/Win32")

# Include stb_image directory
include_directories("Dependencies/stb_image")

find_package(OpenGL REQUIRED)

add_subdirectory(src)


