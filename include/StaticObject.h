#pragma once
#include"GameObject.h"
class StaticObject :public GameObject
{
public:
	using GameObject::GameObject;
	StaticObject(const sf::Texture& texture, std::shared_ptr<b2World> world, sf::Vector2f pos);
	//	StaticObject()=default;
	//virtual void draw(sf::RenderWindow& target) const ;

protected:
	
private:
	virtual void CreateBody(sf::Vector2f pos);
};