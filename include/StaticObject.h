#pragma once
#include"GameObject.h"
class StaticObject :public GameObject
{
public:
	using GameObject::GameObject;
	StaticObject(Resources::TEXTURE, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::SOUNDS sound);
	//	StaticObject()=default;
	//virtual void draw(sf::RenderWindow& target) const ;

protected:
	
private:
	virtual void CreateBody(sf::Vector2f pos);
};