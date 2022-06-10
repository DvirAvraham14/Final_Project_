#include "CollisionHandler.h"
#include "Spike.h"
#include "Jake.h"
#include "Tricky.h"
#include "Ground.h"
#include "Railing.h"
#include "Spikes.h"
#include"Truck.h"
#include "EndFlag.h"
#include "Monster.h"
#include "Coin.h"



// primary collision-processing functions
void groundOnJump(GameObject& Ground, GameObject& scate, bool feetToch, bool endTouch)
{
	auto scateTouch = static_cast<PlayerVehicles*>(&scate);

	if (feetToch) {
		scate.startContact();
		scateTouch->setRotate(false);
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
	auto scateTouchRailing = static_cast<PlayerVehicles*>(&scate);

	if (feetToch) {
		std::cout << "feet\n";
		railing.play();
	}
	else if(!endTouch && !feetToch){
		//scateTouchRailing->setEnableMove(false);
		scateTouchRailing->setSpeet(-15);

	}
	if (endTouch) {
		railing.stopPlay();
		scateTouchRailing->setEnableMove(true);
		scateTouchRailing->setRotate(true);
	}
}

// secondary collision-processing functions that just
// implement symmetry: swap the parameters and call a
// primary function
void oppsiteScateRailing(GameObject& railing, GameObject& scate, bool feetToch, bool endTouch)
{
	scateRailing(scate, railing, feetToch, endTouch);
}

void scateSpikes(GameObject& scate, GameObject& spikes, bool feetToch, bool endTouch)
{
		
	if (scate.getSprite().getGlobalBounds().intersects(spikes.getSprite().getGlobalBounds())) {
		auto obj = static_cast<PlayerVehicles*>(&scate);
		spikes.play();
		obj->jump(50);
		//obj->setAni(Direction::FrontFall);
	if (endTouch)
		scate.undoCollision();
	}

}


void oppsiteScateSpikes(GameObject& spikes, GameObject& scate, bool feetToch, bool endTouch)
{
	scateSpikes(scate, spikes, feetToch, endTouch);
}


void scateEndFlag(GameObject& scate, GameObject& endFlag, bool feetToch, bool endTouch)
{
	auto scateTouchflag = static_cast<PlayerVehicles*>(&scate);
	scateTouchflag->setSpeet(-10);
	scateTouchflag->setAni(Direction::Win);
	endFlag.play();
	endFlag.stopBody();
}


void oppsiteEndFlag(GameObject& endFlag, GameObject& scate, bool feetToch, bool endTouch)
{
	scateEndFlag(scate, endFlag, feetToch, endTouch);
}


void scateMonster(GameObject& scate, GameObject& monster, bool feetToch, bool endTouch)
{
	monster.play();
}


void oppsiteScateMonster(GameObject& monster, GameObject& scate, bool feetToch, bool endTouch)
{
	scateMonster(scate, monster, feetToch, endTouch);
}

void oppsiteScateCoin(GameObject& coin, GameObject& scate, bool feetToch, bool endTouch)
{
	scateCoin(scate, coin, feetToch, endTouch);
}


void scateCoin(GameObject& scate, GameObject& coin, bool feetToch, bool endTouch)
{
	coin.removeObj();
}



void scateTruck(GameObject& scate, GameObject& truck, bool feetToch, bool endTouch)
{
	truck.play();
	auto truckTouchscate = static_cast<Truck*>(&truck);
	auto scateTouchTruck = static_cast<PlayerVehicles*>(&scate);
	truckTouchscate->setEnableMove(false);
	scateTouchTruck->setEnableMove(false);
	scateTouchTruck->setAni(Direction::FrontFall);
}


void oppsiteScateTruck(GameObject& scate, GameObject& truck, bool feetToch, bool endTouch)
{
	scateTruck(truck, scate, feetToch, endTouch);
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

void truckCoin(GameObject& truck, GameObject& coin, bool feetToch, bool endTouch) {
	coin.undoCollision();
}

void oppsiteTruckCoin(GameObject& coin, GameObject& truck, bool feetToch, bool endTouch)
{
	truckRailing(coin, truck, feetToch, endTouch);
}

void SpikesTruck(GameObject& spikes, GameObject& truck, bool feetToch, bool endTouch)
{
	if (feetToch)
		truck.setGravity(0);
	else
		truck.setGravity(1);
}

void SpikesTruckOP(GameObject& truck, GameObject& spikes, bool feetToch, bool endTouch)
{
	SpikesTruck(spikes, truck, feetToch, endTouch);
}

CollisionHandler::HitMap CollisionHandler::initializeCollisionMap()
{
	HitMap phm;
	setCollisionPlayer<Spike>(phm);
	setCollisionPlayer<Tricky>(phm);
	setCollisionPlayer<Jake>(phm);
	//spike

	phm[Key(typeid(Truck), typeid(Railing))] = &truckRailing;
	phm[Key(typeid(Railing), typeid(Truck))] = &oppsiteTruckRailing;
	phm[Key(typeid(Truck), typeid(Monster))] = &truckMonster;
	phm[Key(typeid(Monster), typeid(Truck))] = &oppsiteTruckMonster;
	phm[Key(typeid(Truck), typeid(Coin))] = &truckCoin;
	phm[Key(typeid(Coin), typeid(Truck))] = &oppsiteTruckCoin;
	phm[Key(typeid(Spikes), typeid(Truck))] = &SpikesTruck;
	phm[Key(typeid(Truck), typeid(Spikes))] = &SpikesTruckOP;
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

void CollisionHandler::processCollision(GameObject& object1, GameObject& object2, bool feetTouch, bool endTouch)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
		return;// "Unknown type";
	phf(object1, object2, feetTouch, endTouch);
}

template<typename T>
void CollisionHandler::setCollisionPlayer(HitMap &phm) {
	phm[Key(typeid(Ground), typeid(T))] = &groundOnJump;
	phm[Key(typeid(T), typeid(Ground))] = &groundOnJumpOP;
	phm[Key(typeid(T), typeid(Railing))] = &scateRailing;
	phm[Key(typeid(Railing), typeid(T))] = &oppsiteScateRailing;
	phm[Key(typeid(T), typeid(Spikes))] = &scateSpikes;
	phm[Key(typeid(Spikes), typeid(T))] = &oppsiteScateSpikes;
	phm[Key(typeid(T), typeid(Monster))] = &scateMonster;
	phm[Key(typeid(Monster), typeid(T))] = &oppsiteScateMonster;
	phm[Key(typeid(T), typeid(Truck))]		= &scateTruck;
	phm[Key(typeid(Truck), typeid(T))]		= &oppsiteScateTruck;
	phm[Key(typeid(T), typeid(EndFlag))]	= &scateEndFlag;
	phm[Key(typeid(EndFlag), typeid(T))]	= &oppsiteEndFlag;
	phm[Key(typeid(T), typeid(Coin))]		= &scateCoin;
	phm[Key(typeid(Coin), typeid(T))]		= &oppsiteScateCoin;
}
