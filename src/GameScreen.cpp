#include "GameScreen.h"

GameScreen::GameScreen(std::shared_ptr<sf::View> view)
	:m_world(std::make_shared<b2World>(b2Vec2(0, 9.8))), m_view(view)
{
	m_world->SetContactListener(&m_contactListner);
	createObj();
	updateLevel();
	setGameInfo();
}

void GameScreen::updateLevel() {

	restartInfo();
	m_map.createMap(GameData::instance().getLevel());
	m_objects.push_back(std::make_unique<Ground>(m_map.getRoad(), m_world));
	m_enemies.push_back(std::make_unique<Truck>(res::TEXTURE::Truck, m_world, sf::Vector2f(100, 500),
		res::Players::P_Truck, res::SOUNDS::Crash));
	createObstacles();
	createCoins();
}

void GameScreen::restartInfo() {
	//if (m_vehicels[GameData::instance().getPlayer()]->getIsEnd())
		//GameData::instance().updateLevel(1);
	m_screenDelay = 2;
	m_coinCount = 0;
	m_timePass -= m_timePass;
	m_objects.clear();
	m_enemies.clear();
	m_vehicels[GameData::instance().getPlayer()]->setSpeet(0);
	m_vehicels[GameData::instance().getPlayer()]->setEnd(false);
	m_vehicels[GameData::instance().getPlayer()]->setEnableMove(true);
	m_vehicels[GameData::instance().getPlayer()]->setIsDead(false);
	m_vehicels[GameData::instance().getPlayer()]->setPosition({ 250, 500 });
	m_vehicels[GameData::instance().getPlayer()]->setAni(Direction::Start);
}

void GameScreen::createObj() {

	m_vehicels.push_back(std::make_unique<Tricky>(res::TEXTURE::TrickyTexture, m_world, res::SOUNDS::Coins));
	m_vehicels.push_back(std::make_unique<Spike>(res::TEXTURE::SpikeTexture, m_world, res::SOUNDS::Coins));
	m_vehicels.push_back(std::make_unique<Jake>(res::TEXTURE::JackTexture, m_world, res::SOUNDS::Coins));
}

void GameScreen::createObstacles() {

	
	std::vector<sf::Vector3f> obstacles = m_map.getObstacels();
	for (auto& obstacle : obstacles) {
		switch (int(obstacle.x)) {
		case RAILING:
			m_objects.push_back(std::make_unique<Railing>(res::TEXTURE::RAILING, m_world, sf::Vector2f(obstacle.y, obstacle.z), res::SOUNDS::SLIDE));
			break;
		case SPIKES:
			m_objects.push_back(std::make_unique<Spikes>(res::TEXTURE::SPIKES,
				m_world, sf::Vector2f(obstacle.y, obstacle.z), res::SOUNDS::KnifeStab));
			break;
		case FLAG:
			m_objects.push_back(std::make_unique<EndFlag>(res::TEXTURE::Flag,
				m_world, sf::Vector2f(obstacle.y, obstacle.z-20), res::SOUNDS::Winning));
			break;
		case MONSTER:
			m_enemies.push_back(std::make_unique<Monster>(res::TEXTURE::Monster,
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
				m_objects.push_back(std::make_unique<Coin>(res::TEXTURE::Coin,
					m_world, sf::Vector2f(coin.m_pos.y + j, coin.m_pos.z - 20), res::SOUNDS::Coins));
				m_totalCoins++;
			}
		else

			for (auto i = 0, j = 0; i < coin.m_pos.x; i++, j += map::COINS_DIS) {
				if (i > coin.m_pos.x / 2)
					j -= 2 * map::COINS_DIS;
				m_objects.push_back(std::make_unique<Coin>(res::TEXTURE::Coin,
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

	sf::Text text;
	text.Bold;
	text.setFont(m_font);
	text.setColor(sf::Color::Black);
	text.setScale(1.4, 1.4);

	GameData::instance().setClockText(text);
	GameData::instance().setCoinText(text);

}
void GameScreen::handleGame(sf::Time& delta) {

	m_gameBg.setTexture(Resources::instance().getTexture(GameData::instance().getCurrBg(), true));
	m_gameBg.setTextureRect(sf::IntRect(0, 0, int(WIDTH_WINDOW * 100), int(HEIGHT_WINDOW * 2.5)));
	m_gameBg.setScale(WIDTH_WINDOW / 2000.f, WIDTH_WINDOW / 2000.6f);

	m_vehicels[GameData::instance().getPlayer()]->setBox2dEnable(true);

	if (static_cast<Ground*>(m_objects[GROUND].get())->getEndPoint() - m_vehicels[GameData::instance().getPlayer()]->getPos().x > WIDTH_WINDOW)
		m_view->setCenter(sf::Vector2f(m_vehicels[GameData::instance().getPlayer()]->getPos()).x + WIDTH_WINDOW / 3.f, HEIGHT_WINDOW / 1.5f);

	m_world->Step(timeStep, velocityIterations, positionIterations);

	m_vehicels[GameData::instance().getPlayer()]->update(delta);
	for (auto& enemy : m_enemies)
		enemy->update(delta);

	for (auto i = 0; i < m_objects.size(); i++) {
		m_objects[i]->update(delta);
		if (m_objects[i]->getDeleteStatus()) {
			m_objects.erase(m_objects.begin() + i);
			m_vehicels[GameData::instance().getPlayer()]->play();
			m_coinCount++;
		}
	}
	if (screenTimer(delta))
		return;
	m_timePass += delta;
	setClock();
	updateCoinsInfo();
	updateClockInfo();
	if (m_vehicels[GameData::instance().getPlayer()]->getIsEnd() || m_vehicels[GameData::instance().getPlayer()]->isDead()) {
		GameData::instance().setClockString(m_time, { 638, 370 });
		GameData::instance().setCoinString(std::to_string(m_coinCount), { 403, 370 });
		GameData::instance().setStars(scoreCalculator());
		updateLevel();
		GameData::instance().setScreen(SCORE);
	}
}

bool GameScreen::screenTimer(sf::Time delta) {
	if ((m_vehicels[GameData::instance().getPlayer()]->getIsEnd() || m_vehicels[GameData::instance().getPlayer()]->isDead())
		&& m_screenDelay >= 0) {
		m_screenDelay -= delta.asSeconds();
		return true;
	}
	return false;
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

	m_vehicels[GameData::instance().getPlayer()]->draw(target);
	for (auto& enemy : m_enemies)
		enemy->draw(target);

	//m_world->DebugDraw();
	target.draw(GameData::instance().getClockText());
	target.draw(m_clockInfo);
	target.draw(GameData::instance().getCoinText());
	target.draw(m_coinInfo);
}

void GameScreen::updateCoinsInfo()  {

	m_coinInfo.setPosition(m_view->getCenter().x + 300, HEIGHT_WINDOW / 5.f);

	std::ostringstream oss;
	oss << "X " << m_coinCount;
	GameData::instance().setCoinString(oss.str(), { m_view->getCenter().x + 360, HEIGHT_WINDOW / 4.75f });
}

void GameScreen::updateClockInfo() {
	m_clockInfo.setPosition(m_view->getCenter().x + 90, HEIGHT_WINDOW / 4.6f);
	
	std::ostringstream oss;
	oss << "X " << m_time;
	GameData::instance().setClockString(oss.str(), { m_view->getCenter().x + 136, HEIGHT_WINDOW / 4.75f });
}
