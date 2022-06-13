#include "GameScreen.h"

Resources::TEXTURE GameScreen::m_choosenBg = Resources::TEXTURE::CITY_NIGHT;

GameScreen::GameScreen(std::shared_ptr<b2World> world, std::shared_ptr<sf::View> view)
	:m_world(world), m_view(view)
{
	updateLevel();
}

void GameScreen::updateLevel() {

	m_level++;
	m_map.createMap(m_level);
	m_objects.clear();
	m_vehicels.clear();
	m_enemies.clear();
	m_coinCount = 0;
	createObj();
}


void GameScreen::createObj() {

	m_objects.push_back(std::make_shared<Ground>(m_level, m_map.getRoad(), m_world));

	m_vehicels.push_back(std::make_shared<Tricky>(res::TEXTURE::TrickyTexture, m_world, res::SOUNDS::Coins));
	m_vehicels.push_back(std::make_shared<Spike>(res::TEXTURE::SpikeTexture, m_world, res::SOUNDS::Coins));
	m_vehicels.push_back(std::make_shared<Jake>(res::TEXTURE::JackTexture, m_world, res::SOUNDS::Coins));

	m_enemies.push_back(std::make_shared<Truck>(res::TEXTURE::Truck, m_world, sf::Vector2f(150, 550),
		res::Players::P_Truck, res::SOUNDS::Crash));

	createObstacles();
	createCoins();

}

void GameScreen::createObstacles() {

	std::vector<sf::Vector3f> obstacles = m_map.getObstacels();
	for (auto& obstacle : obstacles) {
		switch (int(obstacle.x)) {
		case RAILING:
			m_objects.push_back(std::make_shared<Railing>(res::TEXTURE::RAILING, m_world, sf::Vector2f(obstacle.y, obstacle.z), res::SOUNDS::SLIDE));
			break;
		case SPIKES:
			m_objects.push_back(std::make_shared<Spikes>(res::TEXTURE::SPIKES,
				m_world, sf::Vector2f(obstacle.y, obstacle.z), res::SOUNDS::KnifeStab));
			break;
		case FLAG:
			m_objects.push_back(std::make_shared<EndFlag>(res::TEXTURE::Flag,
				m_world, sf::Vector2f(obstacle.y, obstacle.z), res::SOUNDS::Winning, false));
			break;
		case MONSTER:
			m_enemies.push_back(std::make_shared<Monster>(res::TEXTURE::Monster,
				m_world, sf::Vector2f(obstacle.y, obstacle.z),
				res::Players::P_Monster, res::SOUNDS::KnifeStab));
			break;

		}
	}
}

void GameScreen::createCoins() {
	std::vector<CoinData> coins = m_map.getCoins();

	for (auto& coin : coins) {
		if (coin.m_isLine)
			for (auto i = 0, j = 0; i < coin.m_pos.x; i++, j += map::COINS_DIS) {
				m_objects.push_back(std::make_shared<Coin>(res::TEXTURE::Coin,
					m_world, sf::Vector2f(coin.m_pos.y + j, coin.m_pos.z - 20), res::SOUNDS::Coins));
				m_totalCoins++;
			}
		else

			for (auto i = 0, j = 0; i < coin.m_pos.x; i++, j += map::COINS_DIS) {
				if (i > coin.m_pos.x / 2)
					j -= 2 * map::COINS_DIS;
				m_objects.push_back(std::make_shared<Coin>(res::TEXTURE::Coin,
					m_world, sf::Vector2f(coin.m_pos.y + i * map::COINS_DIS, coin.m_pos.z - j - 20), res::SOUNDS::Coins));
				m_totalCoins++;
			}
	}
}

void GameScreen::handleGame(sf::Time& delta) {

	m_gameBg.setTexture(Resources::instance().getTexture(m_choosenBg, true));
	m_gameBg.setTextureRect(sf::IntRect(0, 0, int(WIDTH_WINDOW * 100), int(HEIGHT_WINDOW * 2.5)));
	m_gameBg.setScale(WIDTH_WINDOW / 2000.f, WIDTH_WINDOW / 2000.6f);

	m_vehicels[SelectVehicle::getPlayer()]->setBox2dEnable(true);

	if (static_cast<Ground*>(m_objects[GROUND].get())->getEndPoint() - m_vehicels[SelectVehicle::getPlayer()]->getPos().x > WIDTH_WINDOW)
		m_view->setCenter(sf::Vector2f(m_vehicels[SelectVehicle::getPlayer()]->getPos()).x + WIDTH_WINDOW / 3.f, HEIGHT_WINDOW / 1.5f);

	m_world->Step(timeStep, velocityIterations, positionIterations);
	m_timePass += delta;

	m_vehicels[SelectVehicle::getPlayer()]->update(delta);
	for (auto& enemy : m_enemies)
		enemy->update(delta);

	for (auto i = 0; i < m_objects.size(); i++) {
		m_objects[i]->update(delta);
		if (m_objects[i]->getDeleteStatus()) {
			m_objects.erase(m_objects.begin() + i);
			m_vehicels[SelectVehicle::getPlayer()]->play();
			m_coinCount++;
		}
	}
	if (m_vehicels[SelectVehicle::getPlayer()]->getIsEnd()) {
		ScoreScreen::setNumOfStars(scoreCalculator());
		updateLevel();
	}

	setClock();
}

int GameScreen::scoreCalculator() {
	
	int stars = 0;

	if (m_timePass.asSeconds() / float(static_cast<Ground*>(m_objects[GROUND].get())->getEndPoint()) < 0.04)
		stars++;
	if (m_coinCount * 2 > m_totalCoins)
		stars++;
	if (m_coinCount == m_totalCoins)
		stars++;
	return stars;
 }

void GameScreen::setClock() {
	int seconds;

	seconds = m_timePass.asSeconds() - 60 * m_minutes;

	if (seconds < 10)
		m_time = std::to_string(m_minutes) + ":" + "0" + std::to_string(seconds);
	else
		m_time = std::to_string(m_minutes) + ":" + std::to_string(seconds);


	if (seconds == 60)
		m_minutes++;
}

void GameScreen::draw(sf::RenderWindow& target) const {
	target.draw(m_gameBg);
	for (auto& obj : m_objects)
		obj->draw(target);

	m_vehicels[SelectVehicle::getPlayer()]->draw(target);
	for (auto& enemy : m_enemies)
		enemy->draw(target);
	//m_world->DebugDraw();
}