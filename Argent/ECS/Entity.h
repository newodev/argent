#include <ECSTypes.h>
#include <Archetypes.h>

namespace ag
{
	// An indexer into an archetype for convenience
	class Entity
	{
	public:
		Entity(EntityID id)
		{
			ID = id;
			archetype = ArchetypeCollection::GetArchetypeFromEntityID(ID);
		}

		template <typename C>
		C* Get()
		{
			int index = archetype->GetIndexByID(ID);
			if (index == -1)
				return nullptr;
			return archetype->GetComponent<C>(index);
		}

		EntityID GetID()
		{
			return ID;
		}

	private:
		EntityID ID;
		ArchetypeCollection* archetype;
	};
}