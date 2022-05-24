#pragma once
#include "Resources.h"
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "box2d/box2d.h"

const int WIDTH_WINDOW = 1024;
const int HEIGHT_WINDOW = 768;

enum class T_Screen
{
	Menu,
	Game,
};

const float SCALAR = 100;
const float timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;