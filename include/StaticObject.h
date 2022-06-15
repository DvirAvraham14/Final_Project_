#pragma once
#include "GameObject.h"
#include "Animation.h"

class StaticObject :public GameObject
{
public:
	StaticObject() = default;
	StaticObject(Resources::TEXTURE, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::SOUNDS sound, bool = true);
	StaticObject(std::shared_ptr<b2World> world, Resources::TEXTURE texture, sf::Vector2f pos, Resources::SOUNDS sound);

protected:
	virtual void CreateBody(sf::Vector2f pos);
};