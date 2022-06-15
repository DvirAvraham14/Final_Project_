#pragma once
#include "PlayerVehicles.h"

class Tricky : public PlayerVehicles
{
public:
	using PlayerVehicles::PlayerVehicles;
	virtual void drive(Resources::Players = Resources::Players::Jake);
	virtual void jump(float = 0, Resources::Players = Resources::Players::Tricky);

private:
};