#include <IDRegistry.h>

ag::ArchetypeCollection* ag::IDRegistry::GetArchetypeFromEntityID(EntityID id)
{
	ArchetypeID archID = id >> EPARTSIZE;
	return archetypes[archID];
}

// Hashes a set of components to an ID
ArchetypeID ag::IDRegistry::GetArchetypeID(ComponentSet components)
{
	std::sort(components.begin(), components.end());
	ArchetypeID result = (ArchetypeID)components.size();
	for (size_t i = 0; i < components.size(); i++)
	{
		result ^= components[i] + 0x9e3779b9 + (result << 6) + (result >> 2);
	}
	return result;
}

void ag::IDRegistry::RegisterArchetype(ArchetypeCollection* archetype)
{
	archetypes.insert(std::pair<ArchetypeID, ArchetypeCollection*>(archetype->GetID(), archetype));
}

void ag::IDRegistry::DeregisterArchetype(ArchetypeID id)
{
	archetypes.erase(id);
}