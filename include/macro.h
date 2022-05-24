#pragma once
#include "Resources.h"
#include <SFML\Audio.hpp>
#include <regex> 
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
const int WIDTH_WINDOW = 1024;
const int HEIGHT_WINDOW = 768;

enum class T_Screen
{
	Menu,
	Game,
};