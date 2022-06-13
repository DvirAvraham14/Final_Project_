#pragma once
#include "MyContactListener.h"
#include "DebugDraw.h"
#include "Screen.h"
#include "Spike.h"
#include "Jake.h"
#include "Tricky.h"
#include "SelectVehicle.h"
#include "Railing.h"
#include "Spikes.h"
#include "Monster.h"
#include "Ground.h"
#include "EndFlag.h"
#include "Truck.h"
#include "Map.h"
#include "Coin.h"
#include "macro.h"
#include "ScoreScreen.h"

class GameScreen :public Screen
{
public:
	using res = Resources;
	GameScreen(std::shared_ptr<b2World> world, std::shared_ptr<sf::View> view);
	virtual void draw(sf::RenderWindow& target) const;
	void handleGame(sf::Time& delta);
	void static setBg(Resources::TEXTURE bg) { m_choosenBg = bg; }
	
private:
	void createObj();
	void createObstacles();
	void createCoins();
	void setGameInfo();
	void updateLevel();
	void setClock();
	int scoreCalculator();
	void updateCoinsInfo();
	void updateClockInfo();

	sf::Text                                    m_coinText;
	sf::Text                                    m_clockText;
	sf::Font                                    m_font;
	sf::Sprite                                  m_clockInfo;
	sf::Sprite                                  m_coinInfo;
	bool                                        m_lost = false;
	std::string                                 m_time;
	int                                         m_minutes = 0;
	Resources::TEXTURE static                   m_choosenBg;
	std::shared_ptr<sf::View>					m_view;
	sf::Sprite                                  m_gameBg;
	sf::Time									m_timePass;
	int							                m_level		= 0;
	int                                         m_totalCoins = 0;
	int							                m_coinCount = 0;
	Map                                         m_map;
	std::shared_ptr<b2World>                    m_world;
	std::vector<std::shared_ptr<GameObject>>	m_objects;
	std::vector<std::shared_ptr<MovingObject>>	m_vehicels;
	std::vector<std::shared_ptr<MovingObject>>	m_enemies;

	
};