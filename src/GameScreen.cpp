#include"GameScreen.h"
GameScreen::GameScreen(std::shared_ptr<b2World> world,std::shared_ptr<sf::View> view)
	:m_world(world), m_view(view)//,Screen(res::TEXTURE::CITY_NIGHT, GAME)
{
	updateLevel();
	createObj();
}
void GameScreen::draw(sf::RenderWindow& target) const {
	//target.draw(m_background);
	for (auto& obj : m_objects)
		obj->draw(target);

	m_vehicels[0]->draw(target);
	for (auto& enemy : m_enemies)
		enemy->draw(target);
}
void GameScreen::createObj() {

	m_objects.push_back(std::make_shared<Ground>(m_level, m_map.getRoad(), m_world));
	m_vehicels.push_back(std::make_shared<Scate>(res::TEXTURE::SpikeTexture, m_world, sf::Vector2f(200, 500),
		res::Players::Spike, res::SOUNDS::LANDING));

	m_enemies.push_back(std::make_shared<Truck>(res::TEXTURE::Truck, m_world, sf::Vector2f(0, 550),
		res::Players::Enemy, res::SOUNDS::Crash));

	std::vector<sf::Vector3f> obstacles = m_map.getObstacels();
	for (auto& obstacle : obstacles) {
		switch (int(obstacle.x)) {
		case 1:
			m_objects.push_back(std::make_shared<Railing>(res::TEXTURE::RAILING, m_world, sf::Vector2f(obstacle.y, obstacle.z), res::SOUNDS::SLIDE));
			break;
		case 2:
			m_objects.push_back(std::make_shared<Spikes>(res::TEXTURE::SPIKES,
				m_world, sf::Vector2f(obstacle.y, obstacle.z), res::SOUNDS::KnifeStab));
			break;
		case 3:
			m_objects.push_back(std::make_shared<EndFlag>(res::TEXTURE::Flag,
				m_world, sf::Vector2f(obstacle.y, obstacle.z), res::SOUNDS::Winning));
			break;
		case 4:
			m_enemies.push_back(std::make_shared<Monster>(res::TEXTURE::Monster,
				m_world, sf::Vector2f(obstacle.y, obstacle.z),
				res::Players::Enemy, res::SOUNDS::KnifeStab));
			break;

		}
	}
}
void GameScreen::updateLevel() {

	m_map.createMap(m_level);
}
void GameScreen::handleScreen(sf::Event event, const sf::Vector2f cursorPos) {
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
		static_cast<MovingObject*>(m_vehicels[0].get())->changeAni();

	if (static_cast<Ground*>(m_objects[0].get())->getEndPoint() - m_vehicels[0]->getPos().x > WIDTH_WINDOW)
		m_view->setCenter(sf::Vector2f(m_vehicels[0]->getPos()).x + 350.0f, (HEIGHT_WINDOW / 2)+150);

	m_world->Step(timeStep, velocityIterations, positionIterations);
	const auto delta = m_gameClock.restart();

	m_vehicels[0]->update(delta);
	for (auto& enemy : m_enemies)
		enemy->update(delta);
}
