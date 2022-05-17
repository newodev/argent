# CMakeList.txt : CMake project for Argent, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
include_directories("D:/gamedev/Libraries/glm/")
include_directories("D:/gamedev/Libraries/glfw3.3.7/include/")

# Add source to this project's executable.
add_executable (Argent "Argent.cpp" "Argent.h")

# TODO: Add tests and install targets if needed.
