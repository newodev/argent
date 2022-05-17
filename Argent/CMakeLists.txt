# CMakeList.txt : CMake project for Argent, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
include_directories("D:/gamedev/Libraries/glm/")
include_directories("D:/gamedev/Libraries/glfw3.3.7/include/")
include_directories("D:/Vulkan/Include/")



# Add source to this project's executable.
add_executable (Argent "VulkanTest.cpp" "Argent.h")

target_link_libraries(Argent "D:/Vulkan/Lib/vulkan-1.lib")
target_link_libraries(Argent "D:/gamedev/Libraries/glfw3.3.7/lib-vc2022/glfw3.lib")

# TODO: Add tests and install targets if needed.
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestShaders/trianglef.spv ${CMAKE_CURRENT_BINARY_DIR}/TestShaders/trianglef.spv COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestShaders/trianglev.spv ${CMAKE_CURRENT_BINARY_DIR}/TestShaders/trianglev.spv COPYONLY)