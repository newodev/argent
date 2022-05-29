#pragma once

#include <ECSTypes.h>
#include <atomic>

namespace ag
{
	class Component
	{
	public:
		// Generates a unique ID for each type
		// trick from @nice_byte
		template <typename T>
		static ComponentTypeID GetID()
		{
			static ComponentTypeID id = ++nextComponentID;
			return id;
		}

	private:
		static std::atomic<ComponentTypeID> nextComponentID;
		
	};
}

