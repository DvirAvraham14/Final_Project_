#pragma once
#include <typeinfo>
#include <map>
#include <string>
#include <typeindex>
#include "GameObject.h"
class SelectVehicle;

class CollisionHandler {
public:

	using HitFunctionPtr = void (*)(GameObject&, GameObject&, bool, bool);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	static CollisionHandler& instance();
	void   processCollision(GameObject& object1, GameObject& object2, bool, bool = false);
	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2);
	HitMap initializeCollisionMap();
private:
	template<typename T>
	void setCollisionPlayer(HitMap& table);
	template<typename T>
	void setTruckCollision(HitMap& table);

	void setMonsterCollision(HitMap& table);
	CollisionHandler() = default;
	CollisionHandler(const CollisionHandler&) = delete;
	void operator=(const CollisionHandler&) = delete;

};

void groundOnJump(GameObject& Ground, GameObject& scate, bool = false, bool = false);
void groundOnJumpOP(GameObject& scate, GameObject& ground, bool = false, bool = false);
void scateRailing(GameObject& scate, GameObject& ground, bool = false, bool = false);
void oppsiteScateRailing(GameObject& scate, GameObject& ground, bool = false, bool = false);
void scateSpikes(GameObject& scate, GameObject& spikes, bool = false, bool = false);
void oppsiteScateSpikes(GameObject& spikes, GameObject& scate, bool = false, bool = false);

void spikeMonster(GameObject& spike, GameObject& monster, bool = false, bool = false);
void oppsiteSpikeMonster(GameObject& monster, GameObject& spike, bool = false, bool = false);

void staticCollision(GameObject& truck, GameObject& staticObj, bool feetToch, bool endTouch);
void oppsiteStaticCollision(GameObject& staticObj, GameObject& railing, bool feetToch, bool endTouch);

void oppsiteScateCoin(GameObject& coin, GameObject& scate, bool = false, bool = false);
void scateCoin(GameObject& scate, GameObject& coin, bool = false, bool = false);