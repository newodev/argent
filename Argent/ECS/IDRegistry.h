#pragma once

#include <ECS.h>
#include <atomic>

namespace ag
{
	class IDRegistry
	{
	public:
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
		
	};
}

