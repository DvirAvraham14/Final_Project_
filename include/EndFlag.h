#pragma once

#include"StaticObject.h"

class EndFlag :public StaticObject
{
public:
	EndFlag(Resources::TEXTURE texture,std::shared_ptr<b2World> world,sf::Vector2f pos,Resources::SOUNDS sound);
	~EndFlag() = default;
	void update(sf::Time);

private:
	Animation m_animation;
};