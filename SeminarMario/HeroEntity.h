#pragma once
#include "Entities.h"
#include "opencv2/opencv.hpp"
//#include "HeroEntity.h"
#include "Config.h"
#include <memory>
#include <filesystem>
using namespace cv;
using namespace std;
bool checkPixelLevelCollisionBottom(IPhysicsComponentPtr const first, IPhysicsComponentPtr const& other);
bool checkOnTheFloor(IPhysicsComponentPtr const& first, cv::Mat floor);
class Singleton;  // Forward declaration of Singleton class

enum HeroStates {
	HERO_IDLE,
	HERO_RUN_RIGHT,
	HERO_RUN_LEFT,
	HERO_DUCK,
	HERO_STAY_DUCK,
	HERO_STAND_AFTER_DUCK,
	HERO_JUMP,
	HERO_FALL
};

namespace fs = std::filesystem;
class HeroEntity :public Entity
{
public:
	HeroEntity(std::string const& rootAnimationsFolder, int height, int width);
	virtual void onNotify(Event const& e) override;
	EntityStatePtr createHeroState(fs::path const& animationFolder, HeroStates state, int height, int width);
	EntityPtr createHero(std::string const& rootAnimationsFolder, int height, int width);
};
typedef std::shared_ptr<HeroEntity> HeroEntityPtr;





//#pragma once
//
//#include "Entities.h"
//
//EntityPtr createHero(std::string const& rootAnimationsFolder, int height, int width);
