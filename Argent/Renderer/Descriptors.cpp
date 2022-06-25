#include <Descriptors.h>

//////////// Descriptor Allocator ///////////////
void ag::DescriptorAllocator::Initialise(vk::Device d)
{
	device = d;
}

void ag::DescriptorAllocator::Cleanup()
{
	for (vk::DescriptorPool p : freePools)
		device.destroyDescriptorPool(p);

	for (vk::DescriptorPool p : usedPools)
		device.destroyDescriptorPool(p);
}

vk::DescriptorPool CreatePool(vk::Device device, const ag::DescriptorAllocator::PoolSizes& poolSizes, int count, vk::DescriptorPoolCreateFlags flags)
{
	std::vector<vk::DescriptorPoolSize> sizes;
	sizes.reserve(poolSizes.Sizes.size());
	for (auto e : poolSizes.Sizes)
	{
		sizes.push_back({ e.first, uint32_t(e.second * count) });
	}

	vk::DescriptorPoolCreateInfo info(flags, count, sizes);
	return device.createDescriptorPool(info);
}

vk::DescriptorPool ag::DescriptorAllocator::GrabPool()
{
	// Use a free pool if possible
	if (freePools.size() > 0)
	{
		vk::DescriptorPool free = freePools.back();
		freePools.pop_back();

		return free;
	}
	// Else we create a new one
	else
	{
		return CreatePool(device, descriptorSizes, 1000, {});
	}
}

