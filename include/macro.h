#pragma once
#include <SFML\Audio.hpp>
#include "box2d/box2d.h"
#include "Resources.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

//__________________Window Data________________________

const unsigned int WIDTH_WINDOW = 1024;
const unsigned int HEIGHT_WINDOW = WIDTH_WINDOW/1.6;

//__________________Game enum__________________________

enum T_Screen
{
	MENU = 0,
	HELP,
	SELECT_VEHICLE,
	SELECT_AREA,
	SELECT_LEVEL,
	SCORE,
	GAME,
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

enum BACKGROUND
{
	NIGHT_CITY_BG = 0,
	SNOW_BG,
	CITY_BG,
	BEACH_BG,

};

//___________________Map Data_______________________

const float timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 7;
const int32 positionIterations = 3;

const std::vector<sf::Vector2f>PIT_VEC = { {0,0},{0,200},{220,200},{220,0} };
const unsigned int PIT_SIZE = 200;

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
const float MAX_SPEED[Resources::Players::MaxPlayer] = { 30,35,25,7,20 };

//________________animation data____________________

const auto AnimationTime = sf::seconds(0.1f);
const float HALF = 2.f;
const unsigned int OFFSET = 30;
const unsigned int RESET = 0;

//_____________Collision Handler data_______________

const int BUMP = -20;
const int SLOW = -10;
const unsigned int HOVER = 0;
const unsigned int GROUNDED = 1;

//____________________Btn data______________________

const sf::Vector2f BTN_SCALE = { WIDTH_WINDOW / 1100.0f, WIDTH_WINDOW / 1100.0f };
const sf::Color HOVERED = sf::Color(0xfafafacc);
const sf::Color ORIGINAL = sf::Color(0xfafafaff);
const sf::Color HOVERED_MAP = sf::Color(0x37373737);
const sf::Color ORIGINAL_MAP = sf::Color(0x00FF000F); 
const sf::Color TRANSPARE = sf::Color{ 0x00FF000F };


//________________Controller data___________________

const unsigned int MUSIC_VOLUME = 70;
const unsigned int LOW_VOLUME = 25;

//__________________Enemy data______________________

const float ENEMY_DENSITY = 1.0f;
const float ENEMY_FRICTION = 1.0f;

//________________Game Screen data__________________

const sf::Vector2f GRAVITY = { 0, 9.8 };
const sf::Vector2f TRUCK_POS = { 120, 500 };
const sf::Vector2f PLAYER_POS = { 300, 500 };
const sf::Vector2f CLOCK_SCALE = { 0.9, 0.8 }; 
const sf::Vector2f COIN_SCALE = { 1, 1.2 }; 
const sf::Vector2f TEXT_SCALE = { 1.4, 1.4 }; 
const sf::Vector2f GAME_SCALE = { WIDTH_WINDOW / 2000.f, WIDTH_WINDOW / 2000.6f };
const sf::Vector2f VIEW_POS = { WIDTH_WINDOW / 3.f, HEIGHT_WINDOW / 1.5f };
const sf::Vector2f CLOCK_POS = { 638, 370 }; 
const sf::Vector2f COIN_POS = { 403, 370 };
const sf::IntRect COIN_RECT = { 0, 50, 50, 50 };
const sf::IntRect GAME_RECT = { 0, 0, int(WIDTH_WINDOW * 100), int(HEIGHT_WINDOW * 2.5) };
const unsigned int MAX_SCORE = 3;
const unsigned int START = 1;
const unsigned int MINUTE = 1;
const unsigned int DELAY = 2; 
const unsigned int GAME_OFFSET = 20; 
const unsigned int END_VIEW = 500;
const unsigned int ONE_MINUTE = 60;
const unsigned int TWO_DIGIT_SEC = 10;
const unsigned int COIN_OFFSET = 300;
const unsigned int CLOCK_OFFSET = 90;
const unsigned int COIN_TEXT_OFFSET = 360;
const unsigned int CLOCK_TEXT_OFFSET = 136;
const float COIN_HEIGHT = HEIGHT_WINDOW / 5.f;
const float CLOCK_HEIGHT = HEIGHT_WINDOW / 4.6f;
const float TEXT_HEIGHT = HEIGHT_WINDOW / 4.75f; 

//________________Ground data____________________

const unsigned int CONST_POINT = 2;
const float FIXTURE = 1.0f;

//_________________Help data_____________________

const sf::Vector2f ARROW_SCALE = { WIDTH_WINDOW / 1420.0f, WIDTH_WINDOW / 1420.0f };
const sf::Vector2f ARROW_LEFT_POS = { 40,HEIGHT_WINDOW / 2.2f };
const sf::Vector2f ARROW_RIGHT_POS = { WIDTH_WINDOW - 40 ,HEIGHT_WINDOW / 2.2f }; 
const float ROAD_THICKNESS = WIDTH_WINDOW / -33.3f; 
const sf::Color ROAD_OUTLINE_COLOR = sf::Color(0x373737FF); 
const sf::Color ROAD_COLOR = sf::Color(0x555555FF);

//_________________Menu data_____________________

const sf::Vector2f LOGO_POS = { WIDTH_WINDOW / 2.f, HEIGHT_WINDOW / 1.17f };
const sf::Vector2f LOGO_SCALE = { WIDTH_WINDOW / 2000.f, WIDTH_WINDOW / 2000.f };
const sf::Vector2f PLAY_POS = { WIDTH_WINDOW / 2.f, HEIGHT_WINDOW / 1.4f };
const sf::Vector2f HELP_POS = { WIDTH_WINDOW / 17, HEIGHT_WINDOW / 10 };
const sf::Vector2f MUTE_POS = { WIDTH_WINDOW / 17, HEIGHT_WINDOW / 4 };
const unsigned int VOLUME = 100;
const unsigned int MUTE = 0;

//________________Monster data___________________

const sf::Vector2f MOVE_LEFT = { -1, 1 }; 
const sf::Vector2f MOVE_RIGHT = { 1, 1 };
const sf::Vector2f MONSTER_POS = { 200, 0 };
const int REVERS = -1;
const float FORCE = 1 / 60.0;
const unsigned int ANGLE = 180;

//___________MyContactListener data_______________

const unsigned int COLLIDE = 1;

//______________PlayerVehicles data_______________

const unsigned int MAX_ROTATION = 45;
const unsigned int FULL_ANGLE = 360;
const unsigned int PUSH = 5; 
const unsigned int RADIUS = 4;
const unsigned int CIRCLE_OFFSET = 40;
const unsigned int ID = 1;
const unsigned int MASS = 10;
const float PLAYER_DENSITY = 1.0f;
const float PLAYER_FRICTION = 0.1f;
const sf::Vector2f PLAYER_SCALE = { 0.6, 0.6 };
const sf::Vector2f BOX_SCALE = { WIDTH_WINDOW / 33.3f, WIDTH_WINDOW / 23.5f };

//_________________Spikes data___________________

const float SPIKES_DENSITY = 0.5f;
const float SPIKES_FRICTION = 0.1f; 
const float SPIKES_BOX = WIDTH_WINDOW / 23.5f;

//____________SelectVehicle data___________________

const unsigned int SPRITE_POS = 22;
const unsigned int ADD = 1;
const sf::Vector2f LEFT_ARROW = { 60, HEIGHT_WINDOW / 2.2f }; 
const sf::Vector2f RIGHT_ARROW = { WIDTH_WINDOW - 60, HEIGHT_WINDOW / 2.2f }; 
const sf::Vector2f SELECT_POS = { WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 1.25f };
const sf::Vector2f PLAYER_SELECTION_POS = { WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 2.5f };
const sf::Vector2f PLAYER_SELECTION_SCALE = { WIDTH_WINDOW / 900, WIDTH_WINDOW / 900 }; 
const sf::Vector2f NAMES_POS = { WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 4.0f };
const sf::Vector2f NAMES_SCALE = { WIDTH_WINDOW / 2222.f, WIDTH_WINDOW / 2222.f };

const std::array<sf::IntRect, 3> PLAYERS_NAME =
{ 
	sf::IntRect{0, 0, 1223 / 3, 123} , 
	sf::IntRect{1226 / 3, 0, 1223 / 3, 123}, 
	sf::IntRect{(1226 / 3) * 2, 0, 1223 / 3, 123} 
};

//____________SelectVehicle area___________________

const unsigned int SPRITE_AREA_POS = 14;

const std::array<sf::IntRect, 4> AREA_NAME =
{
	sf::IntRect{0, 0, 2500 / 4, 122},
	sf::IntRect{2500 / 4, 0, 2500 / 4, 122 },
	sf::IntRect{(2500 / 4) * 2, 0, 2500 / 4, 122 },
	sf::IntRect{(2500 / 4) * 3, 0, 2500 / 4, 122 },
};

//_______________Screen area______________________
const sf::Vector2f BACK_POS = { WIDTH_WINDOW / 17, HEIGHT_WINDOW / 10 };

//_______________Score Screen______________________

const sf::Vector2f COIN_SCORE_POS = { 423, 375 };
const sf::Vector2f CLOCK_SCORE_POS = { 638, 373 };
const sf::Vector2f STAR_SCALE = { 0.25f, 0.25f };
const std::array <sf::Vector2f, 3> STARS_POS =
{
	sf::Vector2f{ 380, 202 },
	sf::Vector2f{ 469, 202 },
	sf::Vector2f{ 559, 202 }
};

//_______________Road Map Screen__________________

const unsigned int BACK_BTN = 0;
const unsigned int LEVELS_BTN = 1;
const sf::Vector2f LOCK_SCALE = { WIDTH_WINDOW / 1420.0f, WIDTH_WINDOW / 1420.0f };
const std::array < sf::Vector2f, 11> LOCK_LEVEL =
{
	sf::Vector2f{ WIDTH_WINDOW / 1.2f ,HEIGHT_WINDOW / 1.35f },
	sf::Vector2f{ WIDTH_WINDOW / 1.435f, HEIGHT_WINDOW / 1.72f },
	sf::Vector2f{ WIDTH_WINDOW / 1.335f, HEIGHT_WINDOW / 3.39f },
	sf::Vector2f{ WIDTH_WINDOW / 1.56f, HEIGHT_WINDOW / 6.8f },
	sf::Vector2f{ WIDTH_WINDOW / 1.915f, HEIGHT_WINDOW / 3.39f },
	sf::Vector2f{ WIDTH_WINDOW / 2.09f, HEIGHT_WINDOW / 1.72f },
	sf::Vector2f{ WIDTH_WINDOW / 2.6f, HEIGHT_WINDOW / 1.35f },
	sf::Vector2f{ WIDTH_WINDOW / 3.2f, HEIGHT_WINDOW / 1.72f },
	sf::Vector2f{ WIDTH_WINDOW / 2.79f, HEIGHT_WINDOW / 3.39f },
	sf::Vector2f{ WIDTH_WINDOW / 4.2f, HEIGHT_WINDOW / 6.8f },
	sf::Vector2f{ WIDTH_WINDOW / 7.6f, HEIGHT_WINDOW / 3.39f }
};