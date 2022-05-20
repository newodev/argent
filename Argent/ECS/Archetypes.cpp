#include <Archetypes.h>

ag::ArchetypeCollection::ArchetypeCollection(ComponentSet components)
{
	ID = IDRegistry::GetArchetypeID(components);
	NextEntityID = ID << EPARTSIZE;

	EntityCount = 0;
	ComponentTypes = components.size();
	data = new ComponentArray[ComponentTypes];
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