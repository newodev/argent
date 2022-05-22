#include <Archetypes.h>

std::unordered_map<ArchetypeID, ag::ArchetypeCollection*> ag::ArchetypeCollection::archetypes{};

ag::ArchetypeCollection::ArchetypeCollection(ComponentSet components)
{
	std::sort(components.begin(), components.end());
	ID = ArchetypeCollection::GetArchetypeID(components);
	NextEntityID = (EntityID)ID << EPARTSIZE;

	EntityCount = 0;

	ComponentTypes = components;
	data = new ComponentArray[ComponentTypes.size()];
}

void ag::ArchetypeCollection::AddComponent(byte* bytes, int i, int n)
{
	data[i].insert(data[i].end(), bytes, bytes + n);
}

EntityID ag::ArchetypeCollection::GetNextID()
{
	return NextEntityID;
	NextEntityID++;
}

void ag::ArchetypeCollection::RegisterArchetype(ArchetypeCollection* archetype)
{
	archetypes.insert(std::pair<ArchetypeID, ArchetypeCollection*>(archetype->GetID(), archetype));
}

void ag::ArchetypeCollection::DeregisterArchetype(ArchetypeID id)
{
	archetypes.erase(id);
}

ag::ArchetypeCollection* ag::ArchetypeCollection::GetArchetypeFromEntityID(EntityID id)
{
	ArchetypeID archID = id >> EPARTSIZE;
	return archetypes[archID];
}

// Hashes a set of components to an ID
ArchetypeID ag::ArchetypeCollection::GetArchetypeID(ComponentSet components)
{
	ArchetypeID result = (ArchetypeID)components.size();
	for (size_t i = 0; i < components.size(); i++)
	{
		result ^= components[i] + 0x9e3779b9 + (result << 6) + (result >> 2);
	}
	return result;
}

