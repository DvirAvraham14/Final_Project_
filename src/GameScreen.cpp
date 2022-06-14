#include "GameScreen.h"

sf::Text GameScreen::m_clockText = sf::Text();
sf::Text GameScreen::m_coinText = sf::Text();
int	GameScreen::m_level = 0;
Resources::TEXTURE GameScreen::m_choosenBg = Resources::TEXTURE::CITY_NIGHT;

GameScreen::GameScreen(std::shared_ptr<b2World> world, std::shared_ptr<sf::View> view)
	:m_world(world), m_view(view)
{
	createObj();
	updateLevel();
	setGameInfo();
}

void GameScreen::updateLevel() {

	restartInfo();
	m_level++;
	m_map.createMap(m_level);
	m_objects.push_back(std::make_shared<Ground>(m_map.getRoad(), m_world));
	m_enemies.push_back(std::make_shared<Truck>(res::TEXTURE::Truck, m_world, sf::Vector2f(100, 500),
		res::Players::P_Truck, res::SOUNDS::Crash));
	createObstacles();
	createCoins();
}

void GameScreen::restartInfo() {
	m_coinCount = 0;
	m_timePass = sf::Time().Zero;
	m_objects.clear();
	m_enemies.clear();
	m_vehicels[SelectVehicle::getPlayer()]->setEnd(false);
	m_vehicels[SelectVehicle::getPlayer()]->setPosition({ 250, 450 });
}

void GameScreen::createObj() {

	m_vehicels.push_back(std::make_shared<Tricky>(res::TEXTURE::TrickyTexture, m_world, res::SOUNDS::Coins));
	m_vehicels.push_back(std::make_shared<Spike>(res::TEXTURE::SpikeTexture, m_world, res::SOUNDS::Coins));
	m_vehicels.push_back(std::make_shared<Jake>(res::TEXTURE::JackTexture, m_world, res::SOUNDS::Coins));
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
				m_world, sf::Vector2f(obstacle.y, obstacle.z-20), res::SOUNDS::Winning));
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

void GameScreen::setGameInfo() {
	m_clockInfo.setTexture(Resources::instance().getTexture(Resources::TEXTURE::CLOCK));
	m_clockInfo.setScale(0.9, 0.8);

	m_coinInfo.setTexture(Resources::instance().getTexture(Resources::TEXTURE::Coin));
	m_coinInfo.setTextureRect(sf::IntRect(0, 50, 50, 50));
	m_coinInfo.setScale(1, 1.2);

	m_font = Resources::instance().getFont();

	m_clockText.Bold;
	m_clockText.setFont(m_font);
	m_clockText.setColor(sf::Color::Black);
	m_clockText.setScale(1.4, 1.4);

	m_coinText = m_clockText;

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
	setClock();
	updateCoinsInfo();
	updateClockInfo();
	if (m_vehicels[SelectVehicle::getPlayer()]->getIsEnd()) {
		m_clockText.setString(m_time);
		m_coinText.setString(std::to_string(m_coinCount));
		ScoreScreen::setNumOfStars(scoreCalculator());
		updateLevel();
	}
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
	target.draw(m_clockText);
	target.draw(m_clockInfo);
	target.draw(m_coinText);
	target.draw(m_coinInfo);
}

void GameScreen::updateCoinsInfo()  {

	m_coinInfo.setPosition(m_view->getCenter().x + 300, HEIGHT_WINDOW / 5.f);

	std::ostringstream oss;
	oss << "X " << m_coinCount;
	m_coinText.setString(oss.str());
	m_coinText.setPosition({ m_view->getCenter().x + 360, HEIGHT_WINDOW / 4.75f });
}

void GameScreen::updateClockInfo() {
	m_clockInfo.setPosition(m_view->getCenter().x + 90, HEIGHT_WINDOW / 4.6f);
	
	std::ostringstream oss;
	oss << "X " << m_time;
	m_clockText.setString(oss.str());
	m_clockText.setPosition({ m_view->getCenter().x + 136, HEIGHT_WINDOW / 4.75f });
}
