#include "SlimeEntity.h"

using namespace cv;
using namespace std;

EntityPtr createSlime(std::string const& animationFolder)
{
	auto slimeEnemy = CreateSlimeEnemy(animationFolder);
	EntityPtr slime(new Entity(slimeEnemy));
	slimeEnemy->update();
	return slime;
}

EntityStatePtr CreateSlimeEnemy(std::string const& animationFolder)
{
	AnimationPtr animation(new Animation(animationFolder));
	bool isCyclic = true;

	IGraphicsComponentPtr graphicsPtr(
		new SingleAnimationGraphics(animation, isCyclic));

	IPhysicsComponentPtr nonCollidingPhysicsPtr =
		make_shared<FixedWidgetPhysics>();

	return make_shared<EntityState>(graphicsPtr, nonCollidingPhysicsPtr);
}