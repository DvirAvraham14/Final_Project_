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
	HELP,
	SELECT_VEHICLE,
	SELECT_AREA,
	SELECT_LEVEL,
	GAME,
	SCORE,
};

enum Players
{
	TRICKY = 0,
	SPIKE,
	JAKE,
};

enum OBJECT
{
	GROUND = 0,
	RAILING,
	SPIKES,
	FLAG,
	MONSTER,
	TRUCK,

};

const float timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 7;
const int32 positionIterations = 3;

const std::vector<sf::Vector2f>PIT_VEC = { {0,0},{0,200},{220,200},{220,0} };
const int PIT_SIZE = 200;
namespace map {
	const char DOT = 'd';
	const char OBSTACLE = 'o';
	const char COINS = 'c';
	const int  COINS_DIS = 60;
}

struct CoinData
{
	sf::Vector3f m_pos;
	bool m_isLine;
};

const float JUMP_HEIGHT[Resources::Players::MaxPlayer] = { 45,40,50,0,0 };
const float MAX_SPEED[Resources::Players::MaxPlayer] = { 30,35,25,10,15 };
