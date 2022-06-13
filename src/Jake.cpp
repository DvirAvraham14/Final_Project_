#include "Jake.h"


void Jake::drive(Resources::Players player) {
	PlayerVehicles::drive(Resources::Players::Jake);
}

void Jake::jump(float height, Resources::Players player) {
	PlayerVehicles::jump(height, Resources::Players::Jake);
}