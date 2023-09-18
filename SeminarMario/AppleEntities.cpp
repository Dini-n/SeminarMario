#include "AppleEntities.h"
#include "Singleton.h"
//#include "Observer.cpp"

AppleEntities::AppleEntities() :Entity(createApple()->getState())
{
}

AppleEntities::~AppleEntities()
{
	
}

void AppleEntities::onNotify(Event const& e)
{
	Entity::onNotify(e);
	Singleton* s;

	if (e.sender == EventSenders::SENDER_KEYBOARD
		&&
		e.type == EventTypes::EVENT_KEY_PRESSED
 		&&
		e.code == EventCodes::KEY_SPACE)
	{
	
		s->getApple()->_state->getPhysics()->reset
		(cv::Point(s->getHeroPlace()));

		s->getApple()->_state->getGraphics()->reset();
	}
	Singleton* p;
	EntitiesPoolPtr aa = p->getSlimePool();
	int n = p->getSlimePool()->getPool().size() - 1;
	for (int i = 0; i < n; i++)
	{
		if (p->getSlimePool()->getIsInUse()[i])
		{

			if (p->getApple()->getState()->getPhysics()->checkCollision(p->getSlimePool()->getPool()[i]->getState()->getPhysics())) {
				p->getSlimePool()->getIsInUse()[i] = false;

				p->getApple()->getState()->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::KILL_ENEMY_WITH_APPLE });
				return;
			}

		}
	}
	
}

EntityPtr AppleEntities::createApple( )
{
	auto state = CreateAppleState();
	EntityPtr apple(new Entity(state));
	state->Register(apple);
	return apple;
}
EntityStatePtr AppleEntities::CreateAppleState()
{
	IGraphicsComponentPtr graphicsPtr(new AppleGraphics());
	IPhysicsComponentPtr nonCollidingPhysicsPtr = (std::make_shared<ThrowPhysics>(15,40,4));
	return std::make_shared<EntityState>(graphicsPtr, nonCollidingPhysicsPtr);
}
