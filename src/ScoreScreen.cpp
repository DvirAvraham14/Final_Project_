#include "ScoreScreen.h"

//___________________________________________________

ScoreScreen::ScoreScreen()
	:Screen(Resources::TEXTURE::Score, T_Screen::SELECT_LEVEL)
{
	createButtons();
	setStarsData();
	m_sound.setBuffer(Resources::instance().getSound(Resources::RATE));
}

//___________________________________________________

void ScoreScreen::createButtons() {

	m_buttons.push_back(Btn(SELECT_POS.x, SELECT_POS.y, Resources::TEXTURE::NEXT,
		[&]() ->T_Screen {GameData::instance().setIsNextLevel(true); return SELECT_LEVEL; }));
}

//___________________________________________________

void ScoreScreen::setStarsData() {

	sf::Sprite star;
	star.setTexture(Resources::instance().getTexture(Resources::TEXTURE::STAR));
	star.setScale(STAR_SCALE);

	for (auto& pos : STARS_POS) {
		star.setPosition(pos);
		m_stars.push_back(star);
	}
}

//___________________________________________________

void ScoreScreen::handleScreen() {
	m_coinText = GameData::instance().getCoinText();
	m_coinText.setColor(sf::Color{ 0x373737FF });
	m_coinText.setOrigin(m_coinText.getGlobalBounds().width / HALF, m_coinText.getGlobalBounds().height / HALF);
	m_coinText.setPosition(COIN_SCORE_POS);

	m_clockText = GameData::instance().getClockText();
	m_clockText.setColor(sf::Color{ 0x373737FF });
	m_clockText.setOrigin(m_clockText.getGlobalBounds().width / HALF, m_clockText.getGlobalBounds().height / HALF);
	m_clockText.setPosition(CLOCK_SCORE_POS);
}

//___________________________________________________

void ScoreScreen::draw(sf::RenderWindow& target) const {
	Draw(target);
	for (auto i = 0; i < GameData::instance().getStars(); i++) {
		target.draw(m_stars[i]);
	}
	target.draw(m_coinText);
	target.draw(m_clockText);
}
