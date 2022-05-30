#include <World.h>

// Traverses the graph to find the archetype with the component set. Creates an archetype on the graph if it can't be found
ag::GraphNode* ag::World::TraverseRight(ag::GraphNode* start, ComponentSet diff)
{
	std::sort(diff.begin(), diff.end());

	GraphNode* position = start;

	// Loop through diff until we've traversed all the way to the desitination
	for (size_t i = 0; i < diff.size(); i++)
	{
		ComponentTypeID current = diff.at(i);
		bool found = false;
		// Search the edges of our position for the next component
		for (size_t j = 0; j < position->edges.size(); j++)
		{
			if (position->edges.at(j).diff == current)
			{
				position = position->edges.at(j).right;
				found = true;
				break;
			}
		}
		// If we didn't find one, make a new node there
		if (!found)
		{
			GraphNode* newNode = new GraphNode();
			GraphEdge link;
			link.left = position;
			link.right = newNode;
			link.diff = current;

			newNode->edges = { link };
			position->edges.push_back(link);

			position = newNode;
		}
	}

	return position;
}