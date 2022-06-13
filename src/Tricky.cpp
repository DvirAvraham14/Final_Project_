#include "Tricky.h"


void Tricky::drive(Resources::Players player) {
	PlayerVehicles::drive(Resources::Players::Tricky);
}

void Tricky::jump(float height, Resources::Players player) {
	PlayerVehicles::jump(height, Resources::Players::Tricky);
}