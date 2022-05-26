# CMakeList.txt : CMake project for Argent, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
include_directories("D:/gamedev/Libraries/glm/")
include_directories("D:/gamedev/Libraries/glfw3.3.7/include/")
include_directories("D:/gamedev/Libraries/stb/")
include_directories("D:/gamedev/Libraries/tinyobj/")
include_directories("D:/Vulkan/Include/")

# Add source to this project's executable.
add_executable (Argent "Argent.h" "VulkanTest.cpp" "Assets/Vertex.h" "Assets/ModelLoader.h" "Assets/TextureLoader.h" "ECS/ECSTypes.h" "ECS/IDRegistry.h"  "ECS/Archetypes.h" "ECS/Archetypes.cpp"  "ECS/Component.cpp" "Renderer/ArgentVk.h" "ECS/Entity.h" "ECS/ECS.h" "Tests/ECSTests.cpp")
target_include_directories(Argent PUBLIC "Assets/")
target_include_directories(Argent PUBLIC "ECS/")
target_include_directories(Argent PUBLIC "Renderer/")
target_link_libraries(Argent "D:/Vulkan/Lib/vulkan-1.lib")
target_link_libraries(Argent "D:/gamedev/Libraries/glfw3.3.7/lib-vc2022/glfw3.lib")

# TODO: For loop here
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestShaders/trianglef.spv ${CMAKE_CURRENT_BINARY_DIR}/TestShaders/trianglef.spv COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestShaders/trianglev.spv ${CMAKE_CURRENT_BINARY_DIR}/TestShaders/trianglev.spv COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestTextures/pepe.jpg ${CMAKE_CURRENT_BINARY_DIR}/TestTextures/pepe.jpg COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestTextures/rock.jpg ${CMAKE_CURRENT_BINARY_DIR}/TestTextures/rock.jpg COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestModels/rock.obj ${CMAKE_CURRENT_BINARY_DIR}/TestModels/rock.obj COPYONLY)