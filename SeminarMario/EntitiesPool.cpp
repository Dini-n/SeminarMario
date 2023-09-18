#include "EntitiesPool.h"
#include <algorithm>

EntitiesPool::EntitiesPool()
{
	_pool.resize(10);
	_isInUse.resize(10, false);
}

void EntitiesPool::insert(EntityPtr whom, int i)
{
	_pool[i] = whom;
	_isInUse[i] = false;
}

EntityPtr EntitiesPool::getNext()
{
	try {
		auto iter = find(_isInUse.begin(), _isInUse.end(), false);
		if (iter != _isInUse.end()) {
			int index = std::distance(_isInUse.begin(), iter);
			_isInUse[index] = true;
			return _pool[index];
		}
		else
			throw "there is no available entity";
	}
	catch (std::string e) {
		std::cout << e;
	}

	return nullptr;
}

std::vector<EntityPtr> EntitiesPool::getPool()
{
	return _pool;
}

std::vector<bool>& EntitiesPool::getIsInUse()
{
	return _isInUse;
}

void EntitiesPool::returnEntity(EntityPtr toFree)
{
	auto iter = find(_isInUse.begin(), _isInUse.end(), true);
	if (iter != _isInUse.end()) {
		int index = std::distance(_isInUse.begin(), iter);
		_isInUse[index] = false;
	}
}
