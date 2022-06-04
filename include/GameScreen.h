#pragma once
#include "MyContactListener.h"
#include "DebugDraw.h"
#include "Screen.h"
#include "Scate.h"
#include "Railing.h"
#include "Spikes.h"
#include "Monster.h"
#include "Ground.h"
#include "EndFlag.h"
#include "Truck.h"
#include "Map.h"
#include "macro.h"

class GameScreen :public Screen
{
public:
	using res = Resources;
	GameScreen(std::shared_ptr<b2World> world, std::shared_ptr<sf::View> view);
	virtual void draw(sf::RenderWindow& target) const;
	virtual void handleScreen(sf::Event event, const sf::Vector2f cursorPos);
private:
	void createObj();
	void updateLevel();
	std::shared_ptr<sf::View>					m_view;
	//sf::View*                                   m_view;
	sf::Clock					                m_gameClock;
	int							                m_level = 1;
	Map                                         m_map;
	std::shared_ptr<b2World>                    m_world;
	std::vector<std::shared_ptr<MovingObject>>	m_vehicels;
	std::vector<std::shared_ptr<MovingObject>>	m_enemies;
	std::vector<std::shared_ptr<GameObject>>	m_objects;
};