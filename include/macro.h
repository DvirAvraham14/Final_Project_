#pragma once
#include <SFML\Audio.hpp>
#include "box2d/box2d.h"
#include "Resources.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

const int WIDTH_WINDOW = 1024;
const int HEIGHT_WINDOW = WIDTH_WINDOW/1.6;

enum T_Screen
{
	MENU = 0,
	SELECT_LEVEL,
	SELECT_VEHICLE,
	SELECT_AREA,
	GAME,
};

enum Players
{
	TRICKY = 0,
	SPIKE,
	JAKE,
};
const float timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 8;
const int32 positionIterations = 3;

namespace map { 
				const char DOT = 'd';
				const char OBSTACLE = 'o';
}
