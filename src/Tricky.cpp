#include "Tricky.h"

//___________________________________________________

void Tricky::drive(Resources::Players player) {
	PlayerVehicles::drive(Resources::Players::Tricky);
}

//___________________________________________________

void Tricky::jump(float height, Resources::Players player) {
	PlayerVehicles::jump(height, Resources::Players::Tricky);
}