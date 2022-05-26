#pragma once

#include <ECSTypes.h>
#include <unordered_map>
#include <algorithm>
#include <atomic>
#include <IDRegistry.h>

namespace ag
{
	struct EntityInfo
	{
		EntityID ID;
		EntityID ParentID;

		EntityInfo(EntityID id, EntityID p)
		{
			ID = id;
			ParentID = p;
		}
	};

	class ArchetypeCollection
	{
	public:

		/// \TODO: Buffer entity spawning
		/// \TODO: Add+Buffer entity destruction


		template <typename... Cs>
		EntityID SpawnEntity(Cs... component)
		{
			return InstantiateEntity(0, component...);
		}

		template <typename... Cs>
		EntityID SpawnChild(EntityID parent, Cs... component)
		{
			return InstantiateEntity(parent, component...);
		}

		template <typename... Cs>
		EntityID InstantiateEntity(EntityID parent, Cs... component)
		{
			EntityID eid = GetNextID();
			entities.push_back(EntityInfo(eid, parent));

			int i = 0;
			// We assume the components are in the order matching the archetype and add them to each component array
			(AddComponent((byte*)&component, i++, sizeof(component)), ...);

			EntityCount++;

			return eid;
		}

		template <typename C>
		C* GetComponent(int i)
		{
			size_t stride = sizeof(C);
			// The component array that stores this component type
			auto ci = std::find(ComponentTypes.begin(), ComponentTypes.end(), ag::IDRegistry::GetComponentID<C>()) - ComponentTypes.begin();
			// Return a pointer to the component
			return (C*)(&data[ci].at(i * stride));
		}

		ArchetypeID GetID()
		{
			return ID;
		}

		int GetIndexByID(EntityID id);

		int GetEntityCount() { return EntityCount; }

		ArchetypeCollection(ComponentSet components);

		static ArchetypeCollection* GetArchetypeFromEntityID(EntityID id);

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

		// Core entity data (a component that every entity has)
		std::vector<EntityInfo> entities;

		void AddComponent(byte* bytes, int i, int n);

		EntityID GetNextID();
		// The ID of the next entity to spawn
		EntityID NextEntityID;

		static std::unordered_map<ArchetypeID, ArchetypeCollection*> archetypes;
		static std::atomic<ArchetypeID> nextArchetypeID;
	};
}

