#include "CollisionHandler.h"
#include "Scate.h"
#include "Map.h"


// primary collision-processing functions
void groundOnJump(GameObject& Ground, GameObject& scate)
{
	scate.startContact();
}

// secondary collision-processing functions that just
// implement symmetry: swap the parameters and call a
// primary function
void groundOnJumpOP(GameObject& scate, GameObject& ground)
{
	groundOnJump(ground, scate);
}



CollisionHandler::HitMap CollisionHandler::initializeCollisionMap()
{
	HitMap phm;
	phm[Key(typeid(Map  ), typeid(Scate))] = &groundOnJump;
	phm[Key(typeid(Scate), typeid(Map  ))] = &groundOnJumpOP;

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

void CollisionHandler::processCollision(GameObject& object1, GameObject& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
		throw "Unknown type";
	phf(object1, object2);
}


