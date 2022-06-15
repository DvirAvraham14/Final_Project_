#pragma once

#include "CollisionHandler.h"

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener() {};
	~MyContactListener() {};
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};


