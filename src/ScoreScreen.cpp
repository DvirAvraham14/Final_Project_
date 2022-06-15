#include "ScoreScreen.h"

ScoreScreen::ScoreScreen()
	:Screen(Resources::TEXTURE::Score, T_Screen::SCORE)
{
	createButtons();
	setStarsPos();
	m_sound.setBuffer(Resources::instance().getSound(Resources::RATE));
}

void ScoreScreen::createButtons() {

	m_buttons.push_back(Btn(WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 1.25f, Resources::TEXTURE::NEXT,
		[&]() ->T_Screen {GameData::instance().setIsNextLevel(true); return SELECT_LEVEL; }));
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

void ScoreScreen::handleScreen() {
	m_coinText = GameData::instance().getCoinText();
	m_coinText.setColor(sf::Color{ 0x373737FF });
	m_coinText.setOrigin(m_coinText.getGlobalBounds().width / 2.f, m_coinText.getGlobalBounds().height / 2.f);
	m_coinText.setPosition(423, 375);

	m_clockText = GameData::instance().getClockText();
	m_clockText.setColor(sf::Color{ 0x373737FF });
	m_clockText.setOrigin(m_clockText.getGlobalBounds().width / 2.f, m_clockText.getGlobalBounds().height / 2.f);
	m_clockText.setPosition(638, 373);
}

void ScoreScreen::draw(sf::RenderWindow& target) const {
	Draw(target);
	for (auto i = 0; i < GameData::instance().getStars(); i++) {
		target.draw(m_stars[i]);
	}
	target.draw(m_coinText);
	target.draw(m_clockText);
}
