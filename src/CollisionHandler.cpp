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
#include "Btn.h"




// primary collision-processing functions
void groundOnJump(GameObject& Ground, GameObject& scate, bool feetToch, bool endTouch)
{
	auto scateTouch = static_cast<PlayerVehicles*>(&scate);

	if (feetToch) {
		scateTouch->setRotate(false);
		std::cout << "feet\n";
	}
	scate.startContact();
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
	scateTouchRailing->setAni(Direction::Drive);

	if (feetToch && !endTouch) {
		scateTouchRailing->setRotate(true);
		scateTouchRailing->startContact();
		railing.play();
		std::cout << "feet\n";
	}
	else if (!endTouch)
		scateTouchRailing->setSpeet(-20);

	if (endTouch)
		railing.stopPlay();

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

	auto obj = static_cast<PlayerVehicles*>(&scate);
	if (scate.getSprite().getGlobalBounds().intersects(spikes.getSprite().getGlobalBounds()) && !obj->isDead()) {
		spikes.play();
		obj->coilliedSpikes();
	}
}


void oppsiteScateSpikes(GameObject& spikes, GameObject& scate, bool feetToch, bool endTouch)
{
	scateSpikes(scate, spikes, feetToch, endTouch);
}


void scateEndFlag(GameObject& scate, GameObject& endFlag, bool feetToch, bool endTouch)
{
	auto scateTouchflag = static_cast<PlayerVehicles*>(&scate);
	if (!scateTouchflag->getIsEnd()) {
		endFlag.play();
		scateTouchflag->setSpeet(-10);
		scateTouchflag->setAni(Direction::Win);
		scateTouchflag->setEnd(true);
		Btn::setScreen(SCORE);
		sf::sleep(sf::milliseconds(1000));
	}
}


void oppsiteEndFlag(GameObject& endFlag, GameObject& scate, bool feetToch, bool endTouch)
{
	scateEndFlag(scate, endFlag, feetToch, endTouch);
}


void spikeMonster(GameObject& spike, GameObject& monster, bool feetToch, bool endTouch)
{
	//monster.play();
	monster.undoCollision();
}


void oppsiteSpikeMonster(GameObject& monster, GameObject& spike, bool feetToch, bool endTouch)
{
	spikeMonster(spike, monster, feetToch, endTouch);
}

void trickyMonster(GameObject& tricky, GameObject& monster, bool feetToch, bool endTouch)
{
	monster.play();
}


void oppsiteTrickyMonster(GameObject& monster, GameObject& tricky, bool feetToch, bool endTouch)
{
	trickyMonster(tricky, monster, feetToch, endTouch);
}

void jakeMonster(GameObject& jake, GameObject& monster, bool feetToch, bool endTouch)
{
	monster.play();
	auto jakeTouchMonster = static_cast<PlayerVehicles*>(&jake);
	jakeTouchMonster->setAni(Direction::FrontFall);
	jakeTouchMonster->setEnableMove(false);
}


void oppsiteJakeMonster(GameObject& monster, GameObject& jake, bool feetToch, bool endTouch)
{
	jakeMonster(jake, monster, feetToch, endTouch);
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
	scateTouchTruck->stopBody();
	scateTouchTruck->setAni(Direction::FrontFall);
}


void oppsiteScateTruck(GameObject& scate, GameObject& truck, bool feetToch, bool endTouch)
{
	scateTruck(truck, scate, feetToch, endTouch);
}




void staticCollision(GameObject& truck, GameObject& staticObj, bool feetToch, bool endTouch) {
	staticObj.undoCollision();
}
void oppsiteStaticCollision(GameObject& staticObj, GameObject& railing, bool feetToch, bool endTouch)
{
	staticCollision(railing, staticObj, feetToch, endTouch);
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

	setMonsterCollision(phm);

	setTruckCollision<Railing>(phm);
	setTruckCollision<Monster>(phm);
	setTruckCollision<Coin>(phm);

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
void CollisionHandler::setCollisionPlayer(HitMap& phm) {
	phm[Key(typeid(Ground), typeid(T))] = &groundOnJump;
	phm[Key(typeid(T), typeid(Ground))] = &groundOnJumpOP;
	phm[Key(typeid(T), typeid(Railing))] = &scateRailing;
	phm[Key(typeid(Railing), typeid(T))] = &oppsiteScateRailing;
	phm[Key(typeid(T), typeid(Spikes))] = &scateSpikes;
	phm[Key(typeid(Spikes), typeid(T))] = &oppsiteScateSpikes;
	phm[Key(typeid(T), typeid(Truck))] = &scateTruck;
	phm[Key(typeid(Truck), typeid(T))] = &oppsiteScateTruck;
	phm[Key(typeid(T), typeid(EndFlag))] = &scateEndFlag;
	phm[Key(typeid(EndFlag), typeid(T))] = &oppsiteEndFlag;
	phm[Key(typeid(T), typeid(Coin))] = &scateCoin;
	phm[Key(typeid(Coin), typeid(T))] = &oppsiteScateCoin;
}

template<typename T>
void CollisionHandler::setTruckCollision(HitMap& phm) {
	phm[Key(typeid(Truck), typeid(T))] = &staticCollision;
	phm[Key(typeid(T), typeid(Truck))] = &oppsiteStaticCollision;
}

void CollisionHandler::setMonsterCollision(HitMap& phm) {
	phm[Key(typeid(Spike), typeid(Monster))] = &spikeMonster;
	phm[Key(typeid(Monster), typeid(Spike))] = &oppsiteSpikeMonster;
	phm[Key(typeid(Tricky), typeid(Monster))] = &trickyMonster;
	phm[Key(typeid(Monster), typeid(Tricky))] = &oppsiteTrickyMonster;
	phm[Key(typeid(Jake), typeid(Monster))] = &jakeMonster;
	phm[Key(typeid(Monster), typeid(Jake))] = &oppsiteJakeMonster;
}