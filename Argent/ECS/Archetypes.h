#pragma once
#include <IDRegistry.h>
#include <ECS.h>

namespace ag
{
	class ArchetypeCollection
	{
	public:
		template <typename... Cs>
		void SpawnEntity(Cs... components)
		{
			entities.push_back(Entity(GetNextID(), 0));

			int i = 0;
			// We assume the components are in the order matching the archetype and add them to each component array
			(AddComponent((byte*)&components, i++, sizeof(components)), ...);
		}

		ArchetypeID GetID()
		{
			return ID;
		}

		ArchetypeCollection(ComponentSet components);
	private:
		ArchetypeID ID;
		// An array of Component vectors
		ComponentArray* data;
		// The amount of component types that make up this archetype
		int ComponentTypes;
		// The amount of entities currently in the collection
		int EntityCount;
		// The ID of the next entity to spawn
		int NextEntityID;
		// Core entity data (a component that every entity has)
		std::vector<Entity> entities;

		void AddComponent(byte* bytes, int i, int n);

		EntityID GetNextID();
	};
}