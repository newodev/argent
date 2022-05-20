#pragma once

#include <Archetypes.h>
#include <atomic>
#include <unordered_map>
#include <algorithm>

namespace ag
{
	class IDRegistry
	{
	public:

		static ArchetypeCollection* GetArchetypeFromEntityID(EntityID id)
		{
			ArchetypeID archID = id >> EPARTSIZE;
			return archetypes[archID];
		}

		// Hashes a set of components to an ID
		static ArchetypeID GetArchetypeID(ComponentSet components)
		{
			std::sort(components.begin(), components.end());
			ArchetypeID result = (ArchetypeID)components.size();
			for (size_t i = 0; i < components.size(); i++)
			{
				result ^= components[i] + 0x9e3779b9 + (result << 6) + (result >> 2);
			}
			return result;
		}

		static void RegisterArchetype(ArchetypeCollection* archetype)
		{
			archetypes.insert(std::pair<ArchetypeID, ArchetypeCollection*>(archetype->GetID(), archetype));
		}

		static void DeregisterArchetype(ArchetypeID id)
		{
			archetypes.erase(id);
		}

		// Generates a unique ID for each type
		// trick from @nice_byte
		template <typename T>
		static int GetComponentID()
		{
			static int id = ++nextComponentID;
			return id;
		}

	private:
		static std::atomic<int> nextComponentID;
		static std::atomic<int> nextArchetypeID;

		static std::unordered_map<ArchetypeID, ArchetypeCollection*> archetypes;
	};
}

std::atomic<int> ag::IDRegistry::nextComponentID(0);
std::atomic<int> ag::IDRegistry::nextArchetypeID(0);