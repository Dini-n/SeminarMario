#include "CoinEntity.h"
#include "Config.h"
#include "Singleton.h"
using namespace cv;
using namespace std;


EntityPtr createCoin(std::string const& animationFolder)
{
	auto state = CreateCointState(animationFolder);
	EntityPtr heart(new Entity(state));
	state->update();
	return heart;
}

EntityStatePtr CreateCointState(std::string const& animationFolder)
{
	AnimationPtr animation(new Animation(animationFolder));
	bool isCyclic = true;

	IGraphicsComponentPtr graphicsPtr(
		new SingleAnimationGraphics(animation, isCyclic));

	IPhysicsComponentPtr nonCollidingPhysicsPtr =
		make_shared<FixedWidgetPhysics>();

	return make_shared<EntityState>(graphicsPtr, nonCollidingPhysicsPtr);
}