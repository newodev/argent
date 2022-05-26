#pragma once

#include <vulkan/vulkan.hpp>

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace ag
{
	class Renderer
	{
	private:
		vk::Instance instance;
		vk::PhysicalDevice gpu;
		vk::Device device;

		// Display Window
		GLFWwindow* window;
		VkSurfaceKHR surface;

	};

	/// \TODO: Buffers could sub-allocate from a single large buffer, ie. they just index into a big block of memory
	///			- See https://developer.nvidia.com/vulkan-memory-management 
	/// \TODO: Use one big memory allocation, and buffers for each usage type
	class Buffer
	{
	public:
		Buffer(const void* data, vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags memType);
		void Update(const void* data);
		void Copy(Buffer dst);
		void Destroy();

	private:
		vk::Buffer buffer;
		vk::DeviceMemory memory;
		vk::DeviceSize size;
	};

	/// \TODO: Keeps track of all the models currently in use, streams in and out, etc
	///			- See indirect rendering
	/// \TODO: https://on-demand.gputechconf.com/gtc/2013/presentations/S3032-Advanced-Scenegraph-Rendering-Pipeline.pdf
	class SceneConstructor
	{
	public:
	private:

	};

	class RenderObject
	{

	};
}