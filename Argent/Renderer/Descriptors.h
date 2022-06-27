#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <unordered_map>
#include <array>
#include <utility>
#include <algorithm>

// inspired by github.com/vblanco20-1
namespace ag
{
	class DescriptorAllocator
	{
	public:
		struct PoolSizes
		{
			std::vector<std::pair<vk::DescriptorType, float>> Sizes =
			{
				{ vk::DescriptorType::eSampler, 0.5f },
				{ vk::DescriptorType::eCombinedImageSampler, 4.0f },
				{ vk::DescriptorType::eSampledImage, 4.0f },
				{ vk::DescriptorType::eStorageImage, 1.0f },
				{ vk::DescriptorType::eUniformTexelBuffer, 1.0f },
				{ vk::DescriptorType::eStorageTexelBuffer, 1.0f },

				{ vk::DescriptorType::eUniformBuffer, 2.0f },
				{ vk::DescriptorType::eUniformBufferDynamic, 1.0f },
				{ vk::DescriptorType::eStorageBuffer, 2.0f },
				{ vk::DescriptorType::eStorageBufferDynamic, 1.0f },

				{ vk::DescriptorType::eInputAttachment, 0.5f }
			};
		};

		void ResetPools();
		bool Allocate(vk::DescriptorSet* set, vk::DescriptorSetLayout layout);

		void Initialise(vk::Device d);
		void Cleanup();

	private:
		vk::Device device;

		vk::DescriptorPool GrabPool();
		vk::DescriptorPool CurrentPool{ nullptr };
		PoolSizes descriptorSizes;
		std::vector<vk::DescriptorPool> usedPools;
		std::vector<vk::DescriptorPool> freePools;
	};

	class DescriptorLayoutCache
	{
	public:

		void Initialise(vk::Device d);
		void Cleanup();

		vk::DescriptorSetLayout CreateDescriptorLayout(vk::DescriptorSetLayoutCreateInfo* createInfo);

		struct DescriptorLayoutInfo
		{
			std::vector<vk::DescriptorSetLayoutBinding> bindings;

			bool operator==(const DescriptorLayoutInfo& other) const;

			size_t hash() const;
		};

	private:

		struct DescriptorLayoutHash 
		{
			std::size_t operator()(const DescriptorLayoutInfo& k) const 
			{
				return k.hash();
			}
		};

		std::unordered_map<DescriptorLayoutInfo, vk::DescriptorSetLayout, DescriptorLayoutHash> layoutCache;
		vk::Device device;
	};
}