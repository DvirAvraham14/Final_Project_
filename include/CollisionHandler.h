#pragma once
#include <typeinfo>
#include <map>
#include <string>
#include <typeindex>
#include "GameObject.h"


class CollisionHandler {
private:

	CollisionHandler() = default;
	CollisionHandler(const CollisionHandler&) = delete;
	void operator=(const CollisionHandler&) = delete;
    
public:

	using HitFunctionPtr = void (*)(GameObject&, GameObject&);
	using Key			 = std::pair<std::type_index, std::type_index>;
	using HitMap		 = std::map<Key, HitFunctionPtr>;

	static CollisionHandler& instance();
	void   processCollision(GameObject& object1, GameObject& object2);
	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2);
	HitMap initializeCollisionMap();
};

	void groundOnJump(GameObject& Ground, GameObject& scate);
	void groundOnJumpOP(GameObject& scate, GameObject& ground);
