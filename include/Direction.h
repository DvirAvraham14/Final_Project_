#pragma once

#include <SFML/Graphics.hpp>

enum Direction
{
    Win,
    Drive,
    Filp,
    Push,
    FrontFall,
    Start,
    MaxDir,
};

const double ALPHA = 0.8;

//sf::Vector2f toVector(Direction dir);
//Direction toDir(/*bool,*/ sf::Vector2f dir);
//std::pair<Direction, sf::Vector2f> getDir(sf::Vector2f current, sf::Vector2f target/*, bool even*/);
