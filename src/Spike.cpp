#include "Spike.h"

void Spike::drive(Resources::Players player) {
	PlayerVehicles::drive(Resources::Players::Spike);
}

void Spike::jump(float height, Resources::Players player) {
	PlayerVehicles::jump(height, Resources::Players::Spike);
}