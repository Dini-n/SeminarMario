#pragma once

#include "Entities.h"
#include <vector>

// Object Pool Design Pattern
class EntitiesPool
{
private:
	std::vector<EntityPtr> _pool;
	std::vector<bool> _isInUse;

public:
	EntitiesPool();

	void insert(EntityPtr whom, int i);

	// throws exception if all entities are in use.
	EntityPtr getNext();
	std::vector<EntityPtr> getPool();
	std::vector<bool>& getIsInUse();

	void returnEntity(EntityPtr toFree);

};
typedef std::shared_ptr<EntitiesPool> EntitiesPoolPtr;
