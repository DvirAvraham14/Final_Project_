#pragma once

#include "Btn.h"
#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite);
    void direction(Direction dir);
    void update(sf::Time delta);
    void AutoSwitch();

private:
    void update();

    const AnimationData&     m_data;
    sf::Time                 m_elapsed = {};
    Direction                m_dir = Direction::Win;
    int                      m_index = RESET;
    sf::Sprite&              m_sprite;
};
