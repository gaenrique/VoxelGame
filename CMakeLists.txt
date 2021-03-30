# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("VoxelGame")

# Linking to GLEW statically
add_compile_definitions(GLEW_STATIC)

add_subdirectory("Dependencies/glfw")

# Linking to libraries and adding include directory for GLEW
include_directories("Dependencies/glew/include")
link_directories("Dependencies/glew/lib/Release/Win32")

find_package(OpenGL REQUIRED)

add_subdirectory(VoxelGame)


