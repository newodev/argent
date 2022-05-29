#pragma once

#include <ECSTypes.h>
#include <unordered_map>
#include <algorithm>
#include <atomic>
#include <Component.h>
#include <Archetypes.h>

namespace ag
{
	// Used to build a graph of similar archetypes to traverse
	struct GraphNode;
	struct GraphEdge
	{
		/*
		*	[ A, B ] ---- [ A, B, C ]
		*	diff : C
		*/
		GraphNode* left;
		GraphNode* right;
		ComponentTypeID diff;
	};
	struct GraphNode
	{
		std::vector<GraphEdge> edges;
		ArchetypeCollection* archetype;
	};
}