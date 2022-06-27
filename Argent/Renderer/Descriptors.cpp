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

bool ag::DescriptorAllocator::Allocate(vk::DescriptorSet* set, vk::DescriptorSetLayout layout)
{
	if (CurrentPool == NULL)
	{
		CurrentPool = GrabPool();
		usedPools.push_back(CurrentPool);
	}

	std::array layouts{ layout };
	vk::DescriptorSetAllocateInfo info(
		CurrentPool, layouts
	);

	vk::Result result = device.allocateDescriptorSets(&info, set);
	bool needNewPool = false;

	if (result == vk::Result::eSuccess)
		return true;

	if (result == vk::Result::eErrorOutOfPoolMemory || result == vk::Result::eErrorFragmentedPool)
		needNewPool = true;

	if (!needNewPool)
		return false;

	// Need new pool
	CurrentPool = GrabPool();
	usedPools.push_back(CurrentPool);
	result = device.allocateDescriptorSets(&info, set);

	if (result == vk::Result::eSuccess)
		return true;

	return false;
}

void ag::DescriptorAllocator::ResetPools()
{
	for (vk::DescriptorPool pool : usedPools)
	{
		device.resetDescriptorPool(pool);
		freePools.push_back(pool);
	}

	usedPools.clear();
	CurrentPool = vk::DescriptorPool();
}

///////////////////// DescriptorLayoutCache //////////////////////////

void ag::DescriptorLayoutCache::Initialise(vk::Device d)
{
	device = d;
}

void ag::DescriptorLayoutCache::Cleanup()
{
	for (auto descriptor : layoutCache)
	{
		device.destroyDescriptorSetLayout(descriptor.second);
	}
}

vk::DescriptorSetLayout ag::DescriptorLayoutCache::CreateDescriptorLayout(vk::DescriptorSetLayoutCreateInfo* createInfo)
{
	DescriptorLayoutInfo info;
	info.bindings.reserve(createInfo->bindingCount);
	bool isSorted = true;
	int lastBinding = -1;

	for (size_t i = 0; i < createInfo->bindingCount; i++)
	{
		uint32_t binding = createInfo->pBindings[i].binding;
		info.bindings.push_back(binding);

		if (binding > lastBinding)
			lastBinding = binding;
		else
			isSorted = false;
	}

	if (!isSorted)
	{
		std::sort(info.bindings.begin(), info.bindings.end(), [](vk::DescriptorSetLayoutBinding& a, vk::DescriptorSetLayoutBinding& b)
		{
			return a.binding < b.binding;
		});
	}

	auto grab = layoutCache.find(info);
	if (grab != layoutCache.end())
	{
		return (*grab).second;
	}

	// Create a new layout in the cache
	vk::DescriptorSetLayout layout;
	device.createDescriptorSetLayout(createInfo, nullptr, &layout);

	layoutCache[info] = layout;
	return layout;
}

bool ag::DescriptorLayoutCache::DescriptorLayoutInfo::operator==(const DescriptorLayoutInfo& other) const
{
	if (other.bindings.size() != bindings.size())
		return false;

	for (size_t i = 0; i < bindings.size(); i++)
	{
		bool eq = other.bindings[i].binding != bindings[i].binding
			|| other.bindings[i].descriptorType != bindings[i].descriptorType
			|| other.bindings[i].descriptorCount != bindings[i].descriptorCount
			|| other.bindings[i].stageFlags != bindings[i].stageFlags;

		if (!eq)
			return false;
	}

	return true;
}

size_t ag::DescriptorLayoutCache::DescriptorLayoutInfo::hash() const
{
	using std::size_t;
	using std::hash;

	size_t result = hash<size_t>()(bindings.size());
	for (const vk::DescriptorSetLayoutBinding& b : bindings)
	{
		size_t subhash = b.binding 
			| (int)b.descriptorType << 8 
			| (int)b.descriptorCount << 16 
			| (uint32_t)b.stageFlags << 24;

		result ^= hash<size_t>()(subhash);
	}

	return result;
}

