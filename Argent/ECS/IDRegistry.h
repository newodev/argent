#pragma once

#include <ECS.h>
#include <atomic>
#include <unordered_map>
#include <algorithm>
#include <Archetypes.h>

namespace ag
{
	class IDRegistry
	{
	public:

		static ArchetypeCollection* GetArchetypeFromEntityID(EntityID id);

		// Hashes a set of components to an ID
		static ArchetypeID GetArchetypeID(ComponentSet components);

		static void RegisterArchetype(ArchetypeCollection* archetype);

		static void DeregisterArchetype(ArchetypeID id);

		// Generates a unique ID for each type
		// trick from @nice_byte
		template <typename T>
		static ComponentTypeID GetComponentID()
		{
			static ComponentTypeID id = ++nextComponentID;
			return id;
		}

	private:
		static std::atomic<ComponentTypeID> nextComponentID;
		static std::atomic<ComponentTypeID> nextArchetypeID;

		static std::unordered_map<ArchetypeID, ArchetypeCollection*> archetypes;
	};
}

std::atomic<ComponentTypeID> ag::IDRegistry::nextComponentID(0);
std::atomic<ComponentTypeID> ag::IDRegistry::nextArchetypeID(0);