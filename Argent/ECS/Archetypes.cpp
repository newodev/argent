#include <Archetypes.h>

std::unordered_map<ArchetypeID, ag::ArchetypeCollection*> ag::ArchetypeCollection::archetypes{};
std::atomic<ArchetypeID> ag::ArchetypeCollection::nextArchetypeID(0);

ag::ArchetypeCollection::ArchetypeCollection(ComponentSet components)
{
	std::sort(components.begin(), components.end());
	ID = ++nextArchetypeID;
	RegisterArchetype(this);
	// Initialises the first entity's ID by mapping the archetype ID into the upper bits
	NextEntityID = ((EntityID)ID) << EPARTSIZE;

	ComponentTypes = components;
	data = new ComponentArray[ComponentTypes.size()];
	spawnBuffer = new ComponentArray[ComponentTypes.size()];
}

ag::ArchetypeCollection::~ArchetypeCollection()
{
	delete[] data;
	delete[] spawnBuffer;
}

void ag::ArchetypeCollection::AddComponent(byte* bytes, int i, int n, ComponentArray* target)
{
	target[i].insert(target[i].end(), bytes, bytes + n);
}

void ag::ArchetypeCollection::ResolveBuffers()
{
	ResolveDestroyBuffer();
	ResolveSpawnBuffer();
}

void ag::ArchetypeCollection::ResolveDestroyBuffer()
{
	/// \TODO: Would probably be more cache-friendly if u swapped these loop orders
	for (size_t i = 0; i < entitiesToDestroy.size(); i++)
	{
		entities.erase(std::next(entities.begin(), entitiesToDestroy.at(i)));
		for (size_t j = 0; j < ComponentTypes.size(); j++)
		{
			int componentSize = Component::GetSize(ComponentTypes[j]);
			auto start = std::next(data[j].begin(), componentSize * entitiesToDestroy[i]);
			auto end = std::next(start, componentSize);
			data[j].erase(start, end);
		}
	}

	entitiesToDestroy.clear();
}

void ag::ArchetypeCollection::DestroyEntity(int index)
{
	if (index >= entities.size() || index < 0)
		return;

	entitiesToDestroy.push_back(index);
}


void ag::ArchetypeCollection::DestroyEntityByID(EntityID id)
{
	int index = GetIndexByID(id);
	DestroyEntity(index);
}


void ag::ArchetypeCollection::ResolveSpawnBuffer()
{
	// Resize component arrays and copy in new data
	for (size_t i = 0; i < ComponentTypes.size(); i++)
	{
		data[i].insert(data[i].end(), spawnBuffer[i].begin(), spawnBuffer[i].end());
		spawnBuffer[i].clear();
	}
	// Add entity tags too
	entities.insert(entities.end(), entitiesToSpawn.begin(), entitiesToSpawn.end());
	entitiesToSpawn.clear();
}

EntityID ag::ArchetypeCollection::GetNextID()
{
	return NextEntityID++;
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

int ag::ArchetypeCollection::GetIndexByID(EntityID id)
{
	// Binary search for the entity's ID
	int lo = 0;
	int hi = entities.size() - 1;

	while (lo <= hi)
	{
		int mid = (lo + hi) / 2;

		if (id == entities[mid].ID)
			return mid;

		else if (id < entities[mid].ID)
			hi = mid - 1;

		else if (id > entities[mid].ID)
			lo = mid + 1;
	}

	return -1;
}

// Hashes a set of components to an ID
/*
ArchetypeID ag::ArchetypeCollection::GetArchetypeID(ComponentSet components)
{
	ArchetypeID result = (ArchetypeID)components.size();
	for (size_t i = 0; i < components.size(); i++)
	{
		result ^= components[i] + 0x9e3779b9 + (result << 6) + (result >> 2);
	}
	return result;
}
*/
