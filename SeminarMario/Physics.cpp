#include "Physics.h"
#include <algorithm>

using namespace cv;
using namespace std;

/// //////////////////////////////////////////

// @2: Read this function and try to understand what it does. Use Image Watch !
bool checkPixelLevelCollision(IPhysicsComponent const* first, IPhysicsComponentPtr const& other)
{
	cv::Mat const& mask_First = first->getCollisionMask();
	cv::Mat const& mask_Other = other->getCollisionMask();
	if (mask_Other.empty() || mask_First.empty())
		return false;

	Point TL_first = first->getTL();
	Point TL_other = other->getTL();

	// ROI = Reagion of Interest
	Rect firstROI(TL_first, TL_first + Point(mask_First.size()));
	Rect othersROI(TL_other, TL_other + Point(mask_Other.size()));
	Rect intersection = firstROI & othersROI;
	if (intersection.empty())
		return false;

	Rect intersection_RelativeToMe(
		intersection.tl() - TL_first, intersection.br() - TL_first);

	Rect intersection_RelativeToOther(
		intersection.tl() - TL_other, intersection.br() - TL_other);

	Mat myMaskROI = mask_First(intersection_RelativeToMe);
	Mat othersMaskROI = mask_Other(intersection_RelativeToOther);
	Mat whereMeAndOtherIntersect = myMaskROI.mul(othersMaskROI);

	return countNonZero(whereMeAndOtherIntersect);
}
//bool checkPixelLevelCollisionBottom(IPhysicsComponent const* first, IPhysicsComponentPtr const& other)
//{
//	cv::Mat const& mask_First = first->getCollisionMask();
//	cv::Mat const& mask_Other = other->getCollisionMask();
//	if (mask_Other.empty() || mask_First.empty())
//		return false;
//	Point TL_first = first->getTL();
//	Point BR_first = TL_first + Point(mask_First.size());
//	Point BL_first = BR_first - Point(mask_First.size().width, 0);
//	Point TL_other = other->getTL();
//	Point TR_other = TL_other + Point(mask_Other.size().width, 0);
//	//return BL_first.x >= TL_other.x && BR_first.x - 50 <= TR_other.x && abs(BR_first.y - TR_other.y) <= 20;
//	return BL_first.x <= TR_other.x - 100 && BR_first.x >= TL_other.x + 100 && abs(BR_first.y - TR_other.y) <= 15;
//}
/// //////////////////////////////////////////

FixedWidgetPhysics::FixedWidgetPhysics()
	:_topLeft(0, 0), _mask()
{
}

void FixedWidgetPhysics::reset(cv::Point const& tl)
{
	_topLeft = tl;
}

bool FixedWidgetPhysics::update(cv::Mat const& collisionMask)
{
	_mask = collisionMask;
	return false;
}

bool FixedWidgetPhysics::checkCollision(IPhysicsComponentPtr const& other) const
{
	return checkPixelLevelCollision(this, other);
}

cv::Point const& FixedWidgetPhysics::getTL() const
{
	return _topLeft;
}

cv::Mat const& FixedWidgetPhysics::getCollisionMask() const
{
	return _mask;
}

ConstVelocityPhysics::ConstVelocityPhysics(cv::Point const& velocity)
{
	_velocity = velocity;
}

void ConstVelocityPhysics::reset(cv::Point const& tl)
{
	_currTL = tl;
}

bool ConstVelocityPhysics::update(cv::Mat const& collisionMask)
{
	_mask = collisionMask;
	_currTL += _velocity;
	return false;
}

cv::Mat const& ConstVelocityPhysics::getCollisionMask() const
{
	return _mask;
}

bool ConstVelocityPhysics::checkCollision(IPhysicsComponentPtr const& other) const
{
	return checkPixelLevelCollision(this, other);
}

cv::Point const& ConstVelocityPhysics::getTL() const
{
	return _currTL;
}

JumpPhysics::JumpPhysics(int horizontalVelocity, int initialVerticalVelocity, int gravity)
{
	_initialJumpVelocity = cv::Point(horizontalVelocity, -initialVerticalVelocity);
	_currVelocity = _initialJumpVelocity;
	_gravity = gravity;
}

void JumpPhysics::reset(cv::Point const& tl)
{
	_jumpStartTL = tl;
	_currTL = tl;
	_currVelocity = _initialJumpVelocity;
}
//////////////////////////////////////////////////////
bool JumpPhysics::update(cv::Mat const& collisionMask)
{
	_mask = collisionMask;
	_currTL += _currVelocity;
	_currVelocity.y += _gravity;
	if (_currTL.y >= _jumpStartTL.y)
	{
		_currTL.y = _jumpStartTL.y;
	}
	return _currTL.y >= _jumpStartTL.y;;
}

cv::Mat const& JumpPhysics::getCollisionMask() const
{
	return _mask;
}

bool JumpPhysics::checkCollision(IPhysicsComponentPtr const& other) const
{
	return checkPixelLevelCollision(this, other);
}

cv::Point const& JumpPhysics::getTL() const
{
	return _currTL;
}
NonCollidingPhysicsDecorator::NonCollidingPhysicsDecorator(IPhysicsComponentPtr base)
	:_base(base)
{
}

void NonCollidingPhysicsDecorator::reset(cv::Point const& tl)
{
	_base->reset(tl);
}

bool NonCollidingPhysicsDecorator::update(cv::Mat const& collisionMask)
{
	return _base->update(collisionMask);
}

cv::Mat const& NonCollidingPhysicsDecorator::getCollisionMask() const
{
	return Mat();
}

bool NonCollidingPhysicsDecorator::checkCollision(std::shared_ptr<IPhysicsComponent> const& other) const
{
	return _base->checkCollision(other);
}

cv::Point const& NonCollidingPhysicsDecorator::getTL() const
{
	return _base->getTL();
}

BoundedPhysicsDecorator::BoundedPhysicsDecorator(IPhysicsComponentPtr base, int height, int width)
{
	_bounds.width = width;
	_base = base;
	_heightHero = height;
}

void BoundedPhysicsDecorator::test()
{
	//_bounds.contains() ;
	// _base->TL.x < _bounds.x + _bounds.width - _base->getCollisionMask().size().width;
	if (_base->getTL().x > _bounds.width) {
		reset(cv::Point(0, _heightHero));
	}
	if (_base->getTL().x < 0) {
		reset(cv::Point(_bounds.width, _heightHero));
	}
}

void BoundedPhysicsDecorator::reset(cv::Point const& tl)
{
	_base->reset(tl);
}

bool BoundedPhysicsDecorator::update(cv::Mat const& collisionMask)
{
	test();
	return _base->update(collisionMask);
}

cv::Mat const& BoundedPhysicsDecorator::getCollisionMask() const
{
	return _base->getCollisionMask();
}

bool BoundedPhysicsDecorator::checkCollision(std::shared_ptr<IPhysicsComponent> const& other) const
{
	return _base->checkCollision(other);
}

cv::Point const& BoundedPhysicsDecorator::getTL() const
{
	return _base->getTL();
}
//ThrowPhysics::ThrowPhysics(int horizontalVelocity, int initialVerticalVelocity, int gravity)
//	:_gravity(gravity), _initialThrowVelocity(horizontalVelocity, initialVerticalVelocity)
//	, _currVelocity(_initialThrowVelocity)
//{
//	if (gravity < 0 || initialVerticalVelocity < 0)
//		throw exception("A positive number was expected");
//}
//void ThrowPhysics::reset(cv::Point const& tl)
//{
//	_currTL = tl;
//	_currVelocity = _initialThrowVelocity;
//}
//bool ThrowPhysics::update(cv::Mat const& collisionMask)
//{
//	_mask = collisionMask;
//	_currTL += _currVelocity;
//	_currVelocity.y += _gravity;
//
//	return _currTL.y >= _bottom;//return true if the throw is over and false otherwise
//}
//cv::Mat const& ThrowPhysics::getCollisionMask() const
//{
//	return _mask;
//}
//bool ThrowPhysics::checkCollision(IPhysicsComponentPtr const& other) const
//{
//	return checkPixelLevelCollision(this, other);
//}
//cv::Point const& ThrowPhysics::getTL() const
//{
//	return _currTL;
//}
//cv::Point const& ThrowPhysics::getVelocity() const
//{
//	return _currVelocity;
//}

ThrowPhysics::ThrowPhysics(int horizontalVelocity, int initialVerticalVelocity, int gravity)
{
	_initialJumpVelocity = cv::Point(horizontalVelocity, -initialVerticalVelocity);
	_currVelocity = _initialJumpVelocity;
	_gravity = gravity;
}

void ThrowPhysics::reset(cv::Point const& tl)
{
	_jumpStartTL = tl;
	_currTL = tl;
	_currVelocity = _initialJumpVelocity;
}
//////////////////////////////////////////////////////
bool ThrowPhysics::update(cv::Mat const& collisionMask)
{
	_mask = collisionMask;
	_currTL += _currVelocity;
	_currVelocity.y += _gravity;
	/*if (_currTL.y >= 720)
	{
		_currTL.y = 720;
	}*/
	return _currTL.y+20 >= 720;
}

cv::Mat const& ThrowPhysics::getCollisionMask() const
{
	return _mask;
}

bool ThrowPhysics::checkCollision(IPhysicsComponentPtr const& other) const
{
	return checkPixelLevelCollision(this, other);
}

cv::Point const& ThrowPhysics::getTL() const
{
	return _currTL;
}
