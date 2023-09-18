#include "WallEntity.h"
#include "Config.h"
#include "Singleton.h"
using namespace cv;
using namespace std;


EntityPtr createWall(std::string const& animationFolder)
{
	auto state = CreateWallState(animationFolder);
	EntityPtr heart(new Entity(state));
	state->update();
	return heart;
}

EntityStatePtr CreateWallState(std::string const& animationFolder)
{
	AnimationPtr animation(new Animation(animationFolder));
	bool isCyclic = true;

	IGraphicsComponentPtr graphicsPtr(
		new SingleAnimationGraphics(animation, isCyclic));

	IPhysicsComponentPtr nonCollidingPhysicsPtr =
		make_shared<FixedWidgetPhysics>();

	return make_shared<EntityState>(graphicsPtr, nonCollidingPhysicsPtr);
}