#include "Jake.h"

//___________________________________________________

void Jake::drive(Resources::Players player) {
	PlayerVehicles::drive(Resources::Players::Jake);
}

//___________________________________________________

void Jake::jump(float height, Resources::Players player) {
	PlayerVehicles::jump(height, Resources::Players::Jake);
}