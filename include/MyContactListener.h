#pragma once
#include "macro.h"
#include "CollisionHandler.h"


class MyContactListener : public b2ContactListener
{
public:
	MyContactListener() {};
	~MyContactListener() {};
	void BeginContact(b2Contact* contact);
};
