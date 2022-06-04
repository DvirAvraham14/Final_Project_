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

	using HitFunctionPtr = void (*)(GameObject&, GameObject&, bool, bool);
	using Key			 = std::pair<std::type_index, std::type_index>;
	using HitMap		 = std::map<Key, HitFunctionPtr>;

	static CollisionHandler& instance();
	void   processCollision(GameObject& object1, GameObject& object2, bool , bool= false);
	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2);
	HitMap initializeCollisionMap();
};

	void groundOnJump(GameObject& Ground, GameObject& scate, bool = false, bool = false);
	void groundOnJumpOP(GameObject& scate, GameObject& ground, bool = false, bool = false);
	void scateRailing(GameObject& scate, GameObject& ground, bool = false,bool = false);
	void oppsiteScateRailing(GameObject& scate, GameObject& ground, bool = false, bool = false);
	void scateSpikes(GameObject& scate, GameObject& spikes, bool = false, bool = false);
	void oppsiteScateSpikes(GameObject& spikes, GameObject& scate, bool = false, bool = false);
	void scateMonster(GameObject& scate, GameObject& monster, bool = false, bool = false);
	void oppsiteScateMonster(GameObject& monster, GameObject& scate, bool = false, bool = false);

	void truckRailing(GameObject& truck, GameObject& railing, bool = false, bool = false);
	void oppsiteTruckRailing(GameObject& railing, GameObject& truck, bool = false, bool = false);
	void truckMonster(GameObject& truck, GameObject& monster, bool = false, bool = false);
	void oppsiteTruckMonster(GameObject& monster, GameObject& truck, bool = false, bool = false);