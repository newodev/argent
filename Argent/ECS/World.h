#pragma once

#include <Graph.h>

namespace ag
{
	class World
	{
	public:

	private:
		GraphNode* root;
		GraphNode* TraverseRight(GraphNode* start, ComponentSet diff);
	};
}
