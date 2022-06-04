#include "CollisionHandler.h"
#include "Scate.h"
#include "Ground.h"
#include "Railing.h"
#include "Spikes.h"
#include"Truck.h"
#include "EndFlag.h"
#include "Monster.h"


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
	auto scateTouchRailing = static_cast<Scate*>(&scate);
	if (feetToch)
		railing.play();
	else 
		scateTouchRailing->drive(-20);
	
	if (endTouch) 
		railing.stopPlay();
}

// secondary collision-processing functions that just
// implement symmetry: swap the parameters and call a
// primary function
void oppsiteScateRailing(GameObject& railing, GameObject& scate, bool feetToch, bool endTouch)
{
	scateRailing(railing, scate, feetToch, endTouch);
}

void scateSpikes(GameObject& scate, GameObject& spikes, bool feetToch, bool endTouch)
{
	auto obj = static_cast<Scate*>(&scate);
	obj->startContact();
	spikes.play();
	obj->jump(20);
}


void oppsiteScateSpikes(GameObject& spikes, GameObject& scate, bool feetToch, bool endTouch)
{
	scateSpikes(spikes, scate, feetToch, endTouch);
}


void scateEndFlag(GameObject& scate, GameObject& endFlag, bool feetToch, bool endTouch)
{
	endFlag.play();
	endFlag.stopBody();
}


void oppsiteEndFlag(GameObject& endFlag, GameObject& scate, bool feetToch, bool endTouch)
{
	scateEndFlag(endFlag, scate, feetToch, endTouch);
}


void scateMonster(GameObject& scate, GameObject& monster, bool feetToch, bool endTouch)
{
	monster.play();
}


void oppsiteScateMonster(GameObject& monster, GameObject& scate, bool feetToch, bool endTouch)
{
	scateMonster(monster, scate, feetToch, endTouch);
}

void scateTruck(GameObject& scate, GameObject& truck, bool feetToch, bool endTouch)
{
	truck.play();
	std::cout << "LOST";
}


void oppsiteScateTruck(GameObject& monster, GameObject& truck, bool feetToch, bool endTouch)
{
	scateTruck(monster, truck, feetToch, endTouch);
}




void truckRailing(GameObject& truck, GameObject& railing, bool feetToch, bool endTouch) {
	railing.undoCollision();
}
void oppsiteTruckRailing(GameObject& railing, GameObject& truck, bool feetToch, bool endTouch)
{
	truckRailing(railing, truck, feetToch, endTouch);
}

void truckMonster(GameObject& truck, GameObject& monster, bool feetToch, bool endTouch)
{
	monster.undoCollision();
}

void oppsiteTruckMonster(GameObject& monster, GameObject& truck, bool feetToch, bool endTouch)
{
	truckMonster(monster, truck, feetToch, endTouch);
}


CollisionHandler::HitMap CollisionHandler::initializeCollisionMap()
{
	HitMap phm;
	phm[Key(typeid(Ground), typeid(Scate))] = &groundOnJump;
	phm[Key(typeid(Scate), typeid(Ground))] = &groundOnJumpOP;
	phm[Key(typeid(Scate), typeid(Railing))] = &scateRailing;
	phm[Key(typeid(Railing), typeid(Scate))] = &oppsiteScateRailing;
	phm[Key(typeid(Scate), typeid(Spikes))] = &scateSpikes;
	phm[Key(typeid(Spikes), typeid(Scate))] = &oppsiteScateSpikes;
	phm[Key(typeid(Scate), typeid(Monster))] = &scateMonster;
	phm[Key(typeid(Monster), typeid(Scate))] = &oppsiteScateMonster;
	phm[Key(typeid(Scate), typeid(EndFlag))] = &scateEndFlag;
	phm[Key(typeid(EndFlag), typeid(Scate))] = &oppsiteEndFlag;

	phm[Key(typeid(Scate), typeid(Truck))] = &scateTruck;
	phm[Key(typeid(Truck), typeid(Scate))] = &oppsiteScateTruck;

	phm[Key(typeid(Truck), typeid(Railing))] = &truckRailing;
	phm[Key(typeid(Railing), typeid(Truck))] = &oppsiteTruckRailing;
	phm[Key(typeid(Truck), typeid(Monster))] = &truckMonster;
	phm[Key(typeid(Monster), typeid(Truck))] = &oppsiteTruckMonster;
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


