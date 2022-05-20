#pragma once

#include <ECS.h>
#include <atomic>
#include <unordered_map>

namespace ag
{

	class IDRegistry
	{
	public:
		// Maps a set of component types to a

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


	};
}

std::atomic<int> ag::IDRegistry::nextComponentID(0);
std::atomic<int> ag::IDRegistry::nextArchetypeID(0);