#include "LiveEntity.h"
#include "Config.h"
#include "Singleton.h"

LiveEntity::LiveEntity() :Entity(createLives()->getState())
{
}

void LiveEntity::onNotify(Event const& e)
{
	Entity::onNotify(e);
	Singleton* p;

	if (e.sender == EventSenders::SENDER_ENTITY_STATE
		&&
		e.type == EventTypes::EVENT_PHYSICS
		&&
		e.code == EventCodes::COLLISION_WITH_ENEMY)
	{
		p->getHeart()->getState()->getGraphics()->reset(-1);
		//if(p->getHeart()->getState()->getGraphics()->)
	}
	if (e.sender == EventSenders::SENDER_ENTITY_STATE
		&&
		e.type == EventTypes::EVENT_PHYSICS
		&&
		e.code == EventCodes::KILL_ENEMY_WITH_APPLE)
	{
		p->getHeart()->getState()->getGraphics()->reset(1);
	}
	if (
		e.sender == EventSenders::SENDER_ENTITY_STATE &&
		e.type == EventTypes::EVENT_PHYSICS &&
		e.code == EventCodes::COLLISION_WITH_FOOD_SCORE)
	{
		p->getHeart()->getState()->getGraphics()->reset(1);
		/*p->getCoinPool()->getIsInUse()[0] = false;*/
	}

}

EntityPtr LiveEntity::createLives()
{
	auto state = CreateHeartsState();
	EntityPtr heart(new Entity(state));
	return heart;
}

EntityStatePtr LiveEntity::CreateHeartsState()
{
	IGraphicsComponentPtr graphicsPtr(new LivesGraphics());
	IPhysicsComponentPtr nonCollidingPhysicsPtr = (std::make_shared<FixedWidgetPhysics>());
	return std::make_shared<EntityState>(graphicsPtr, nonCollidingPhysicsPtr);
}
