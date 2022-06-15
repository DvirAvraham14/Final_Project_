#include "MyContactListener.h"

//___________________________________________________

void MyContactListener::BeginContact(b2Contact* contact) {

	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	auto objA = static_cast<GameObject*>(bodyUserDataA);
	void* bodtTagA = contact->GetFixtureA()->GetUserData();

	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	auto objB = static_cast<GameObject*>(bodyUserDataB);
	void* bodtTagB = contact->GetFixtureB()->GetUserData();

	if (!objA || !objB) return;
	CollisionHandler::instance().processCollision(*objA, *objB,
		((int)bodtTagA == COLLIDE || (int)bodtTagB == COLLIDE) ? true : false);
}

//___________________________________________________

void MyContactListener::EndContact(b2Contact* contact) {

	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	auto objA = static_cast<GameObject*>(bodyUserDataA);
	//void* bodtTagA = contact->GetFixtureA()->GetUserData();

	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	auto objB = static_cast<GameObject*>(bodyUserDataB);
	//void* bodtTagB = contact->GetFixtureB()->GetUserData();
	if (!objA || !objB) return;
	CollisionHandler::instance().processCollision(*objA, *objB,false,true);
}