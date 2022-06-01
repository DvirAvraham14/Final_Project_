#include "CollisionHandler.h"
#include "Scate.h"
#include "Ground.h"
#include "Railing.h"


// primary collision-processing functions
void groundOnJump(GameObject& Ground, GameObject& scate, bool feetToch, bool endTouch)
{
	if (feetToch) {
		if (!scate.getContacting()) {
			scate.play();
		}
		scate.startContact();
	}
}

// secondary collision-processing functions that just
// implement symmetry: swap the parameters and call a
// primary function
void groundOnJumpOP(GameObject& scate, GameObject& ground, bool feetToch, bool endTouch)
{
	groundOnJump(ground, scate, feetToch);
}


void scateRailing(GameObject& scate, GameObject& railing, bool feetToch, bool endTouch)
{
	auto s = static_cast<Scate*>(&scate);
	if (feetToch)
		railing.play();
	else
		s->drive(-20);

	if (endTouch) 
		railing.stopPlay();
}

// secondary collision-processing functions that just
// implement symmetry: swap the parameters and call a
// primary function
void oppsiteRailing(GameObject& railing, GameObject& scate, bool feetToch, bool endTouch)
{
	scateRailing(railing, scate, feetToch, endTouch);
}


CollisionHandler::HitMap CollisionHandler::initializeCollisionMap()
{
	HitMap phm;
	phm[Key(typeid(Ground), typeid(Scate))] = &groundOnJump;
	phm[Key(typeid(Scate), typeid(Ground))] = &groundOnJumpOP;

	phm[Key(typeid(Scate), typeid(Railing))] = &scateRailing;
	phm[Key(typeid(Railing), typeid(Scate))] = &oppsiteRailing;

	return phm;
}

CollisionHandler::HitFunctionPtr CollisionHandler::lookup(const std::type_index& class1,
	const std::type_index& class2)
{
	static HitMap collisionMap = initializeCollisionMap();
	auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
	if (mapEntry == collisionMap.end())
		return nullptr;
	return mapEntry->second;
}


CollisionHandler& CollisionHandler::instance()
{
	static CollisionHandler instance;
	return instance;
}

void CollisionHandler::processCollision(GameObject& object1, GameObject& object2, bool feetTouch,bool endTouch)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
		return;// "Unknown type";
	phf(object1, object2, feetTouch, endTouch);
}


