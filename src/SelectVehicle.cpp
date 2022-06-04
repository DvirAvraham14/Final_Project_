#include"SelectVehicle.h"
SelectVehicle::SelectVehicle()
	:Screen(Resources::TEXTURE::SELECTION, T_Screen::SELECT_LEVEL)
{
	creatPlayers();
	createButtons();

	m_names.setTextureRect(m_playerName[currPlayer]);
	m_names.setOrigin(m_names.getGlobalBounds().width / 2, m_names.getGlobalBounds().height / 2);
	m_names.setPosition(WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 4.0f);
	m_names.setTexture(Resources::instance().getTexture(Resources::TEXTURE::NAMES));

 }
void SelectVehicle::createButtons() {

	sf::Sprite arrow;
	arrow.setTexture(Resources::instance().getTexture(Resources::TEXTURE::ARROW));
	arrow.setScale(WIDTH_WINDOW / 1420.0f, WIDTH_WINDOW / 1420.0f);

	m_buttons.push_back(Btn({ WIDTH_WINDOW / 19.0f,HEIGHT_WINDOW / 1.2f }, arrow,
		[&]() ->T_Screen { if (currPlayer == TRICKY) currPlayer = JAKE;  else  currPlayer--;  updateRect(); return SELECT_VEHICLE; }));
	arrow.scale(-1, 1);

	m_buttons.push_back(Btn({ WIDTH_WINDOW / 1.05f,HEIGHT_WINDOW / 1.2f }, arrow,
		[&]() ->T_Screen {if (currPlayer == JAKE) currPlayer = TRICKY; else  currPlayer++;  updateRect(); return SELECT_VEHICLE; }));
	m_buttons.push_back(Btn(WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 1.1f, Resources::TEXTURE::SELECT,
		[]() ->T_Screen {return SELECT_AREA; }));
}
void SelectVehicle::creatPlayers() {
	
	m_playerName.push_back(sf::IntRect(0, 0, 1223 / 3, 123));
	m_playerName.push_back(sf::IntRect(1226 / 3, 0, 1223 / 3, 123));
	m_playerName.push_back(sf::IntRect((1226 / 3)*2, 0, 1223 / 3, 123));
}
void SelectVehicle::updateRect() {
	m_names.setTextureRect(m_playerName[currPlayer]);
}
void SelectVehicle::draw(sf::RenderWindow& target) const {
	Draw(target);
	target.draw(m_names);
}

