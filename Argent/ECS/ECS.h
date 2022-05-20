#pragma once

#include <vector>

// ID structure: AAEEEEEE
typedef uint64_t EntityID;
typedef uint16_t ArchetypeID;
const int EPARTSIZE = 64 - 16;

typedef unsigned char byte;

typedef unsigned char ComponentTypeID;
typedef std::vector<ComponentTypeID> ComponentSet;

typedef std::vector<byte> ComponentArray;

#include <iostream>

namespace ag
{
	struct Entity
	{
		EntityID ID;
		EntityID ParentID;

		Entity(EntityID id, EntityID p)
		{
			ID = id;
			ParentID = p;
		}
	};
}