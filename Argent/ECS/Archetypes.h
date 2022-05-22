#pragma once

#include <ECS.h>
#include <unordered_map>
#include <algorithm>
#include <atomic>
#include <IDRegistry.h>

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

		template <typename C>
		C* GetComponent(int i)
		{
			size_t stride = sizeof(C);
			// The component array that stores this component type
			auto ci = std::find(ComponentTypes.begin(), ComponentTypes.end(), ag::IDRegistry::GetComponentID<C>()) - ComponentTypes.begin();
			// Return a pointer to the component
			return (C*)(&data[ci].at(i));
		}

		ArchetypeID GetID()
		{
			return ID;
		}

		ArchetypeCollection(ComponentSet components);

		static ArchetypeCollection* GetArchetypeFromEntityID(EntityID id);

		// Hashes a set of components to an ID
		static ArchetypeID GetArchetypeID(ComponentSet components);

		static void RegisterArchetype(ArchetypeCollection* archetype);

		static void DeregisterArchetype(ArchetypeID id);

	private:
		ArchetypeID ID;
		// An array of Component vectors
		ComponentArray* data;
		// The component types that make up this archetype
		ComponentSet ComponentTypes;
		// The amount of entities currently in the collection
		int EntityCount;
		// The ID of the next entity to spawn
		int NextEntityID;
		// Core entity data (a component that every entity has)
		std::vector<Entity> entities;

		void AddComponent(byte* bytes, int i, int n);

		EntityID GetNextID();

		static std::unordered_map<ArchetypeID, ArchetypeCollection*> archetypes;
	};
}

