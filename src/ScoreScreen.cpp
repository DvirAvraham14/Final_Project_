#include "ScoreScreen.h"

int ScoreScreen::m_numOfStars = 3;

ScoreScreen::ScoreScreen()
	:Screen(Resources::TEXTURE::Score, T_Screen::SCORE)
{
	createButtons();
	setStarsPos();
}

void ScoreScreen::createButtons() {

	m_buttons.push_back(Btn(WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 1.25f, Resources::TEXTURE::NEXT,
		[&]() ->T_Screen { this->setNextLevel(true); return SELECT_LEVEL; }));
}

void ScoreScreen::setStarsPos() {

	std::vector<sf::Vector2f> starsPos;
	starsPos.push_back({ 380, 202 });
	starsPos.push_back({ 469, 202 });
	starsPos.push_back({ 559, 202 });
	setStarsData(starsPos);
}

void ScoreScreen::setStarsData(std::vector<sf::Vector2f> starsPos) {

	sf::Sprite star;
	star.setTexture(Resources::instance().getTexture(Resources::TEXTURE::STAR));
	star.setScale(0.25f, 0.25f);

	for (auto& pos : starsPos) {
		star.setPosition(pos);
		m_stars.push_back(star);
	}
}

void ScoreScreen::draw(sf::RenderWindow& target) const {
	Draw(target);
	for (auto i = 0; i < m_numOfStars; i++)
		target.draw(m_stars[i]);
}