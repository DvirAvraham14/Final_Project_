#include "GameScreen.h"

//___________________________________________________

GameScreen::GameScreen(std::shared_ptr<sf::View> view)
	:m_world(std::make_shared<b2World>(b2Vec2(GRAVITY.x, GRAVITY.y))), m_view(view)
{
	m_world->SetContactListener(&m_contactListner);
	createObj();
	setGameInfo();
}

//___________________________________________________

void GameScreen::updateLevel() {

	restartInfo();
	restartVehicle();
	setBackground();
	createObstacles();
	createCoins();
}

//___________________________________________________

void GameScreen::restartInfo() {
	m_totalCoins = RESET;
	m_screenDelay = DELAY;
	m_coinCount = RESET;
	m_timePass -= m_timePass;
	m_objects.clear();
	m_enemies.clear();
}

//___________________________________________________

void GameScreen::restartVehicle() {
	m_vehicels[GameData::instance().getPlayer()]->undoCollision(false);
	m_vehicels[GameData::instance().getPlayer()]->setSpeet(RESET);
	m_vehicels[GameData::instance().getPlayer()]->setEnd(false);
	m_vehicels[GameData::instance().getPlayer()]->setEnableMove(true);
	m_vehicels[GameData::instance().getPlayer()]->setIsDead(false);
	m_vehicels[GameData::instance().getPlayer()]->setPosition(PLAYER_POS);
	m_vehicels[GameData::instance().getPlayer()]->setAni(Direction::Win);
}

//___________________________________________________

void GameScreen::setBackground() {
	m_gameBg.setTexture(Resources::instance().getTexture(GameData::instance().getCurrBg(), true));
	m_gameBg.setTextureRect(GAME_RECT);
	m_gameBg.setScale(GAME_SCALE);
}

//___________________________________________________

void GameScreen::createObj() {

	m_vehicels.push_back(std::make_unique<Tricky>(res::TEXTURE::TrickyTexture, m_world, res::SOUNDS::Coins));
	m_vehicels.push_back(std::make_unique<Spike>(res::TEXTURE::SpikeTexture, m_world, res::SOUNDS::Coins));
	m_vehicels.push_back(std::make_unique<Jake>(res::TEXTURE::JackTexture, m_world, res::SOUNDS::Coins));
}

//___________________________________________________

void GameScreen::createObstacles() {

	m_map.createMap(GameData::instance().getLevel());
	m_objects.push_back(std::make_unique<Ground>(m_map.getRoad(), m_world));
	m_enemies.push_back(std::make_unique<Truck>(res::TEXTURE::Truck, m_world, TRUCK_POS,
		res::Players::P_Truck, res::SOUNDS::Crash));

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
				m_world, sf::Vector2f(obstacle.y, obstacle.z- GAME_OFFSET), res::SOUNDS::Winning));
			m_flagEndPos = obstacle.y;
			break;
		case MONSTER:
			m_enemies.push_back(std::make_unique<Monster>(res::TEXTURE::Monster,
				m_world, sf::Vector2f(obstacle.y, obstacle.z),
				res::Players::P_Monster, res::SOUNDS::KnifeStab));
			break;
		}
	}
}

//___________________________________________________

void GameScreen::createCoins() {

	std::vector<CoinData> coins = m_map.getCoins();

	for (auto& coin : coins) {
		if (coin.m_isLine)
			for (auto i = 0, j = 0; i < coin.m_pos.x; i++, j += map::COINS_DIS) {
				m_objects.push_back(std::make_unique<Coin>(res::TEXTURE::Coin,
					m_world, sf::Vector2f(coin.m_pos.y + j, coin.m_pos.z - GAME_OFFSET), res::SOUNDS::Coins));
				m_totalCoins++;
			}
		else

			for (auto i = 0, j = 0; i < coin.m_pos.x; i++, j += map::COINS_DIS) {
				if (i > coin.m_pos.x / HALF)
					j -= HALF * map::COINS_DIS;
				m_objects.push_back(std::make_unique<Coin>(res::TEXTURE::Coin,
					m_world, sf::Vector2f(coin.m_pos.y + i * map::COINS_DIS, coin.m_pos.z - j - GAME_OFFSET), res::SOUNDS::Coins));
				m_totalCoins++;
			}
	}
}

//___________________________________________________

void GameScreen::setGameInfo() {
	m_clockInfo.setTexture(Resources::instance().getTexture(Resources::TEXTURE::CLOCK));
	m_clockInfo.setScale(CLOCK_SCALE);

	m_coinInfo.setTexture(Resources::instance().getTexture(Resources::TEXTURE::Coin));
	m_coinInfo.setTextureRect(COIN_RECT);
	m_coinInfo.setScale(COIN_SCALE);

	m_font = Resources::instance().getFont();

	sf::Text text;
	text.Bold;
	text.setFont(m_font);
	text.setColor(sf::Color::Black);
	text.setScale(TEXT_SCALE);

	GameData::instance().setClockText(text);
	GameData::instance().setCoinText(text);
}

//___________________________________________________

void GameScreen::handleGame(sf::Time& delta) {

	checkRound();
	m_vehicels[GameData::instance().getPlayer()]->setBox2dEnable(true);
	updateView();
	updateObject(delta);
	setClock();
	updateCoinsInfo();
	updateClockInfo();

	if (m_vehicels[GameData::instance().getPlayer()]->getIsEnd() || 
		m_vehicels[GameData::instance().getPlayer()]->isDead())
		handleEnd();
}

//___________________________________________________

void GameScreen::updateView() {
	if (m_flagEndPos - m_vehicels[GameData::instance().getPlayer()]->getPos().x > END_VIEW)
		m_view->setCenter(sf::Vector2f(m_vehicels[GameData::instance().getPlayer()]->getPos()).x + VIEW_POS.x, VIEW_POS.y);
}

//___________________________________________________

void GameScreen::updateObject(sf::Time& delta) {
	m_world->Step(timeStep, velocityIterations, positionIterations);

	m_vehicels[GameData::instance().getPlayer()]->update(delta);

	for (auto& enemy : m_enemies)
		enemy->update(delta);

	for (auto i = 0; i < m_objects.size(); i++) {
		m_objects[i]->update(delta);
		handleObject(i);
	}

	if (screenTimer(delta))
		return;

	m_timePass += delta;
}

//___________________________________________________

void GameScreen::checkRound() {
	if (m_firstRound) {
		updateLevel();
		m_firstRound = false;
	}
}

//___________________________________________________

void GameScreen::handleObject(int i) {
	if (m_objects[i]->getDeleteStatus()) {
		m_objects.erase(m_objects.begin() + i);
		m_vehicels[GameData::instance().getPlayer()]->play();
		m_coinCount++;
	}
}

//___________________________________________________

void GameScreen::handleEnd() {
	GameData::instance().setClockString(m_time, CLOCK_POS);
	GameData::instance().setCoinString(std::to_string(m_coinCount) + "/" + std::to_string(m_totalCoins), COIN_POS);
	GameData::instance().setStars(scoreCalculator());
	GameData::instance().setScreen(SCORE);
	if (m_vehicels[GameData::instance().getPlayer()]->getIsEnd())
		GameData::instance().updateLevel(ADD);
	m_firstRound = true;
}

//___________________________________________________

bool GameScreen::screenTimer(sf::Time delta) {
	if ((m_vehicels[GameData::instance().getPlayer()]->getIsEnd() || 
		m_vehicels[GameData::instance().getPlayer()]->isDead())
		&& m_screenDelay >= 0) {
		m_screenDelay -= delta.asSeconds();
		return true;
	}
	return false;
}

//___________________________________________________

int GameScreen::scoreCalculator() {
	
	int stars = RESET;

	if (m_minutes < MINUTE)
		stars++;
	if (m_coinCount * HALF > m_totalCoins)
		stars++;
	if (m_coinCount == m_totalCoins)
		stars++;
	return stars;
 }

//___________________________________________________

void GameScreen::setClock() {
	int seconds;

	seconds = m_timePass.asSeconds() - ONE_MINUTE * m_minutes;

	if (seconds < TWO_DIGIT_SEC)
		m_time = std::to_string(m_minutes) + ":" + "0" + std::to_string(seconds);
	else
		m_time = std::to_string(m_minutes) + ":" + std::to_string(seconds);


	if (seconds == ONE_MINUTE)
		m_minutes++;
}

//___________________________________________________

void GameScreen::draw(sf::RenderWindow& target) const {
	target.draw(m_gameBg);
	for (auto& obj : m_objects)
		obj->draw(target);

	m_vehicels[GameData::instance().getPlayer()]->draw(target);
	for (auto& enemy : m_enemies)
		enemy->draw(target);

	for (auto& i : m_buttons)
		i.draw(target);

	target.draw(GameData::instance().getClockText());
	target.draw(m_clockInfo);
	target.draw(GameData::instance().getCoinText());
	target.draw(m_coinInfo);
}

//___________________________________________________

void GameScreen::updateCoinsInfo()  {

	m_coinInfo.setPosition(m_view->getCenter().x + COIN_OFFSET, COIN_HEIGHT);

	std::ostringstream oss;
	oss << "X " << m_coinCount;
	GameData::instance().setCoinString(oss.str(), { m_view->getCenter().x + COIN_TEXT_OFFSET, TEXT_HEIGHT });
}

//___________________________________________________

void GameScreen::updateClockInfo() {
	m_clockInfo.setPosition(m_view->getCenter().x + CLOCK_OFFSET, CLOCK_HEIGHT);
	
	std::ostringstream oss;
	oss << "X " << m_time;
	GameData::instance().setClockString(oss.str(), { m_view->getCenter().x + CLOCK_TEXT_OFFSET, TEXT_HEIGHT });
}
