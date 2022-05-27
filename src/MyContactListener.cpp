#include "MyContactListener.h"


void MyContactListener::BeginContact(b2Contact* contact) {

	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	auto objA = static_cast<GameObject*>(bodyUserDataA);

	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	auto objB = static_cast<GameObject*>(bodyUserDataB);

	if (!objA | !objB) return;
	CollisionHandler::instance().processCollision(*objA, *objB);
}