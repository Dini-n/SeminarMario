#include "HeroEntity.h"
#include "LiveEntity.h"
#include "Singleton.h"

EntityStatePtr HeroEntity::createHeroState(
	fs::path const& animationFolder,
	HeroStates state, int height, int width)
{
	AnimationPtr animation(new Animation(animationFolder.string()));
	bool isNotCyclic =
		state == HeroStates::HERO_DUCK ||
		state == HeroStates::HERO_STAND_AFTER_DUCK ||
		state == HeroStates::HERO_JUMP;
	bool isCyclic = !isNotCyclic;
	IGraphicsComponentPtr graphicsPtr(
		new SingleAnimationGraphics(animation, isCyclic));
	IPhysicsComponentPtr physicsPtr = nullptr;
	Size frameSize = graphicsPtr->getCollisionMask().size();
	switch (state)
	{
	case HERO_IDLE:
	{
		IPhysicsComponentPtr physicsP(new FixedWidgetPhysics());
		physicsPtr.reset(new BoundedPhysicsDecorator(physicsP, height, width));
		break;
	}
	case HERO_RUN_RIGHT:
	{
		IPhysicsComponentPtr physicsP(new ConstVelocityPhysics(Point(frameSize.width / 10, 0)));
		physicsPtr.reset(new BoundedPhysicsDecorator(physicsP, height, width));
		break;
	}
	case HERO_RUN_LEFT:
	{
		IPhysicsComponentPtr physicsP(new ConstVelocityPhysics(Point(frameSize.width / -10, 0)));
		physicsPtr.reset(new BoundedPhysicsDecorator(physicsP, height, width));
		break;
	}
	case HERO_DUCK:
	{
		IPhysicsComponentPtr physicsP(new FixedWidgetPhysics());
		physicsPtr.reset(new BoundedPhysicsDecorator(physicsP, height, width));
		break;
	}
	case HERO_STAY_DUCK:
	{
		IPhysicsComponentPtr physicsP(new FixedWidgetPhysics());
		physicsPtr.reset(new BoundedPhysicsDecorator(physicsP, height, width));
		break;
	}
	case HERO_STAND_AFTER_DUCK:
	{
		IPhysicsComponentPtr physicsP(new FixedWidgetPhysics());
		physicsPtr.reset(new BoundedPhysicsDecorator(physicsP, height, width));
		break;
	}
	case HERO_JUMP:
	{
		IPhysicsComponentPtr physicsP(new JumpPhysics(15, 40, 4));
		physicsPtr.reset(new BoundedPhysicsDecorator(physicsP, height, width));
		break;
	}
	case HERO_FALL:
	{
		IPhysicsComponentPtr physicsP(new ConstVelocityPhysics(Point(0, frameSize.width / 10)));
		physicsPtr.reset(new BoundedPhysicsDecorator(physicsP, height, width));
		Singleton* p1;
		break;
	}
	default:
		throw std::exception("Unknown physics state!");
	}
	return make_shared<EntityState>(graphicsPtr, physicsPtr);
}

EntityPtr HeroEntity::createHero(std::string const& rootAnimationsFolder, int height, int width)
{
	fs::path root = rootAnimationsFolder;
	auto idleFolder = root / "idle";
	auto idle = createHeroState(root / "idle", HeroStates::HERO_IDLE, height, width);
	auto runRight = createHeroState(root / "runRight", HeroStates::HERO_RUN_RIGHT, height, width);
	auto jump = createHeroState(root / "jump", HeroStates::HERO_JUMP, height, width);
	auto runLeft = createHeroState(root / "runLeft", HeroStates::HERO_RUN_LEFT, height, width);
	auto duck = createHeroState(root / "duckDown", HeroStates::HERO_DUCK, height, width);
	auto duckStay = createHeroState(root / "duckStay", HeroStates::HERO_STAY_DUCK, height, width);
	auto standAfterDuck = createHeroState(root / "standAfterDuck", HeroStates::HERO_STAND_AFTER_DUCK, height, width);
	auto fall = createHeroState(root / "idle", HeroStates::HERO_FALL, height, width);
	//auto heroKill = createHeroState(root / "idle", HeroStates::HERO_KILL, height, width);
	idle->addState(Event{ EventSenders::SENDER_KEYBOARD, EventTypes::EVENT_KEY_PRESSED, EventCodes::KEY_RIGHT }, runRight);
	idle->addState(Event{ EventSenders::SENDER_KEYBOARD, EventTypes::EVENT_KEY_PRESSED, EventCodes::KEY_LEFT }, runLeft);
	idle->addState(Event{ EventSenders::SENDER_KEYBOARD, EventTypes::EVENT_KEY_PRESSED, EventCodes::KEY_DOWN }, duck);
	idle->addState(Event{ EventSenders::SENDER_KEYBOARD, EventTypes::EVENT_KEY_PRESSED, EventCodes::KEY_UP }, jump);

	runRight->addState(Event{ EventSenders::SENDER_KEYBOARD, EventTypes::EVENT_KEY_PRESSED, EventCodes::KEY_LEFT }, idle);
	runRight->addState(Event{ EventSenders::SENDER_KEYBOARD, EventTypes::EVENT_KEY_PRESSED, EventCodes::KEY_UP }, jump);
	runRight->addState(Event{ EventSenders::SENDER_KEYBOARD, EventTypes::EVENT_KEY_PRESSED, EventCodes::KEY_DOWN }, duck);
	runRight->addState(Event{ EventSenders::SENDER_ENTITY_STATE,EventTypes::EVENT_PHYSICS,EventCodes::COLLISION_WITH_ENEMY }, idle);

	jump->addState(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::ENTITY_PHYSICS_FINISHED }, fall);
	jump->addState(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::STAND }, idle);
	fall->addState(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::STAND }, idle);
	
	runLeft->addState(Event{ EventSenders::SENDER_KEYBOARD, EventTypes::EVENT_KEY_PRESSED, EventCodes::KEY_RIGHT }, idle);
	runLeft->addState(Event{ EventSenders::SENDER_ENTITY_STATE,EventTypes::EVENT_PHYSICS,EventCodes::COLLISION_WITH_ENEMY }, idle);
	//runRight->addState(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_GRAPHICS, EventCodes::ENTITY_FINISHED_ANIMATION }, runRight);
	
	duck->addState(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_GRAPHICS, EventCodes::ENTITY_FINISHED_ANIMATION }, duckStay);
	duckStay->addState(Event{ EventSenders::SENDER_KEYBOARD, EventTypes::EVENT_KEY_PRESSED, EventCodes::KEY_UP }, standAfterDuck);
	
	standAfterDuck->addState(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_GRAPHICS, EventCodes::ENTITY_FINISHED_ANIMATION }, idle);
	
	runLeft->addState(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS , EventCodes::FALL_FROM_SHELF }, fall);
	runRight->addState(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS , EventCodes::FALL_FROM_SHELF }, fall);
	//idle->addState(Event{ EventSenders::SENDER_KEYBOARD, EventTypes::EVENT_KEY_PRESSED, EventCodes::KEY_SPACE }, heroKill);
	
	
	EntityPtr hero(new Entity(idle));
	idle->Register(hero);
	runRight->Register(hero);
	jump->Register(hero);
	runLeft->Register(hero);
	duck->Register(hero);
	duckStay->Register(hero);
	standAfterDuck->Register(hero);
	hero->getState()->Register(hero);
	fall->Register(hero);
	//std::shared_ptr<LiveEntity>e;
	//runRight->Register(e);
	//jump->Register(e);
	//runLeft->Register(e);
	return hero;
}
HeroEntity::HeroEntity(std::string const& rootAnimationsFolder, int height, int width)
	:Entity(createHero(rootAnimationsFolder, height, width)->getState())
{
}
void HeroEntity::onNotify(Event const& e)
{
	Entity::onNotify(e);
	if (e.sender == EventSenders::SENDER_ENTITY_STATE
		&&
		e.type == EventTypes::EVENT_PHYSICS
		&&
		e.code == EventCodes::COLLISION_WITH_ENEMY)
	{
		//צריך להוסיף בדיקה של הולוסוטי אם היא מצד ימין או משמאל
		_state->getPhysics()->reset(cv::Point(_state->getPhysics()->getTL().x - 50, _state->getPhysics()->getTL().y));
		//_state->reset(Point(_state->getPhysics()->getTL().x - 100, ));
	}
	Singleton* p;
	int n = p->getSlimePool()->getPool().size() - 1;
	for (int i = 0; i < n; i++)
	{
		if (p->getSlimePool()->getIsInUse()[i])
		{
			if (p->getHeroEntity()->getState()->getPhysics()->checkCollision(p->getSlimePool()->getPool()[i]->getState()->getPhysics())) {
				_state->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::COLLISION_WITH_ENEMY });
				return;
			}

		}
	}
	//עוד בדיקה אם נפגשתי עם אבן - רגלים
	//לזרוק שהפיזיקה נגמר
	//Singleton* p2;
	//n = p1->getWallPool()->getPool().size() - 1;
	//for (int i = 0; i < n; i++)
	//{
	//	if (p1->getWallPool()->getIsInUse()[i])
	//	{
	//		if (!checkPixelLevelCollisionBottom(p2->getHeroEntity()->getState()->getPhysics(), p1->getWallPool()->getPool()[i]->getState()->getPhysics()))
	//		{

	//			_state->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::FALL_FROM_SHELF });
	//			return;
	//		}
	//	}
	//}
	// 	   	Singleton* p2;
	if (e.sender == EventSenders::SENDER_TIMER
		&&
		e.type == EventTypes::EVENT_TIMER
		&&
		e.code == EventCodes::TIME_TICK)
	{
		Singleton* p1;
		/// <coin>
		/// find if there is a  collision with some coin 
		/// </coin>
		/// <param name="e"></param>
		int lenCoin = p1->getCoinPool()->getPool().size();
		bool isCoin = false;
		for (size_t i = 0; i <lenCoin; i++)
		{
			if (p1->getCoinPool()->getIsInUse()[i])
				if (_state->getPhysics()->checkCollision(p1->getCoinPool()->getPool()[i]->getState()->getPhysics()))
				{
					_state->Notify(Event{ EventSenders::SENDER_ENTITY_STATE ,EventTypes::EVENT_PHYSICS , EventCodes::COLLISION_WITH_FOOD_SCORE });
					p->getCoinPool()->getIsInUse()[i] = false;
					isCoin;
					break;
				}
		}
		if (isCoin)
			return;
		/// <summary>
		/// אם היה התנגשות עם הרצפה
		/// </summary>
		/// <param name="e"></param>
		if ((checkOnTheFloor(_state->getPhysics(), p1->getCanvas())))
		{
			/*EntityPtr e;
			p1->setCurrentWall(e);*/
			p1->setNumCurrntWall(-1);
			_state->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::STAND });
			return;
		}
		/// <summary>
		/// תחפש בכל הכתלים
		/// אם נתקעת במשהו שאתה לא עמדת עליו עד כה 
		/// תעדכן את המצב להיות עמידה 
		/// רק קפיצה ונפילה יקשיבו לזה 
		/// </summary>
		/// <param name="e"></param>
		int lenWall = p1->getWallPool()->getPool().size();
		for (size_t i = 0; i < lenWall; i++)
		{
			IPhysicsComponentPtr wall = p1->getWallPool()->getPool()[i]->getState()->getPhysics();
			EntityPtr en = p1->getCurrentWall();
			if ((/*(p1->getCurrentWall()!= p1->getWallPool()->getPool()[i])*/
				p1->getNumCurrntWall()!=i
				&& p1->getWallPool()->getIsInUse()[i]
					&& checkPixelLevelCollisionBottom(p1->getHeroEntity()->getState()->getPhysics(), wall)))
			{
				//p1->setCurrentWall(p1->getWallPool()->getPool()[i]);
				p1->setNumCurrntWall(i);
				_state->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::STAND });
				_state->getPhysics()->reset(cv::Point(wall->getTL().x, wall->getTL().y - 170));
				return;
			}
		}
		/// <summary>
		/// 	נועד בשביל הליכה 
		///		אם לא נמצא על אף מקום
		/// </summary>
		/// <param name="e"></param>
		/*for (size_t i = 0; i < lenWall; i++)
		{
			IPhysicsComponentPtr wall = p1->getWallPool()->getPool()[i]->getState()->getPhysics();
			IPhysicsComponentPtr wall2 = p1->getHeroEntity()->getState()->getPhysics();
			if (!checkPixelLevelCollisionBottom(p1->getHeroEntity()->getState()->getPhysics(),wall)
				&& !checkOnTheFloor(_state->getPhysics(), p1->getCanvas())
				&& p1->getWallPool()->getIsInUse()[i])
			{
				p1->setNumCurrntWall(-1);
				_state->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::FALL_FROM_SHELF });
				return;
			}
		}*/
		if (p->getNumCurrntWall()>-1&&
			!checkPixelLevelCollisionBottom(p1->getHeroEntity()->getState()->getPhysics(), p1->getWallPool()->getPool()[p1->getNumCurrntWall()]->getState()->getPhysics())
			&& !checkOnTheFloor(_state->getPhysics(), p1->getCanvas())
			&& p1->getWallPool()->getIsInUse()[p->getNumCurrntWall()])
		{
			p1->setNumCurrntWall(-1);
			_state->Notify(Event{ EventSenders::SENDER_ENTITY_STATE, EventTypes::EVENT_PHYSICS, EventCodes::FALL_FROM_SHELF });
			return;
		}
		/// <summary>
		/// אם יש סתם התנגשות שלא יוכל ללכת ויתקע
		///אבל זה לא התנגשות עם הרגלים
		/// </summary>
		/// <param name="e"></param>
		
		for (size_t i = 0; i < lenWall; i++)
		{
			IPhysicsComponentPtr wall = p1->getWallPool()->getPool()[i]->getState()->getPhysics();
			if (_state->getPhysics()->checkCollision(wall) &&
				!checkPixelLevelCollisionBottom(p1->getHeroEntity()->getState()->getPhysics(), wall))
			{
				_state->getPhysics()->reset(cv::Point(_state->getPhysics()->getTL().x - 50, _state->getPhysics()->getTL().y));
			}
		}
	}
}

bool checkOnTheFloor(IPhysicsComponentPtr const& first, Mat floor)
{
	bool tem =std::abs(first->getTL().y - floor.size().height * 2 / 3) <= 35;
	return tem;
}
bool checkPixelLevelCollisionBottom(IPhysicsComponentPtr const first, IPhysicsComponentPtr const& other)
{
	cv::Mat const& mask_First = first->getCollisionMask();
	cv::Mat const& mask_Other = other->getCollisionMask();
	if (mask_Other.empty() || mask_First.empty())
		return false;
	Point TL_first = first->getTL();
	Point BR_first = TL_first + Point(mask_First.size());
	Point BL_first = BR_first - Point(mask_First.size().width, 0);
	Point TL_other = other->getTL();
	Point TR_other = TL_other + Point(mask_Other.size().width, 0);
	//return BL_first.x >= TL_other.x && BR_first.x - 50 <= TR_other.x && abs(BR_first.y - TR_other.y) <= 20;
	return BL_first.x <= TR_other.x - 100 && BR_first.x >= TL_other.x + 100 && abs(BR_first.y - TR_other.y) <=65;
}
