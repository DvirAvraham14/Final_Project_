#include <iostream>
#include "Animation.h"

//___________________________________________________

Animation::Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite)
    : m_data(data), m_dir(dir), m_sprite(sprite)
{
    auto size = m_data.m_data.find(m_dir)->second[m_index];
    m_sprite.setOrigin(size.width / HALF, size.height / HALF + OFFSET);
    update();
}

//___________________________________________________

void Animation::direction(Direction dir)
{
    if (m_dir == dir) return;
    m_dir = dir;
    m_index = RESET;
    update();
}

//___________________________________________________

void Animation::update(sf::Time delta)
{
    AutoSwitch();
    m_elapsed += delta;
    if (m_elapsed >= AnimationTime)
    {
        if ((m_dir == Direction::FrontFall) && m_index == m_data.m_data.find(m_dir)->second.size() - 1)
            return;
        m_elapsed -= AnimationTime;
        ++m_index;
        m_index %= m_data.m_data.find(m_dir)->second.size();
        update();
    }
}

//___________________________________________________

void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data.find(m_dir)->second[m_index]);
}

//___________________________________________________

void Animation::AutoSwitch() {
    if (GameData::instance().getScreen() == GAME && m_dir == Direction::Filp || m_dir == Direction::Start || m_dir == Direction::Push)
        if (m_index == m_data.m_data.find(m_dir)->second.size() - 1) {
            m_dir = Direction::Drive;
            m_index = RESET;
        }
}