#include"SelectVehicle.h"
SelectVehicle::SelectVehicle()
	:Screen(Resources::TEXTURE::SELECTION, T_Screen::SELECT_LEVEL),
	m_ani(Resources::instance().getData(player::Spike), Direction::Win, m_player)
{
	creatPlayers();
	createButtons();
	m_player.setTexture(Resources::instance().getTexture(Resources::TEXTURE::SpikeTexture));
	m_player.setPosition(WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 2.0f);
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
		[&]() ->T_Screen { return changePlayer(false); }));
	arrow.scale(-1, 1);

	m_buttons.push_back(Btn({ WIDTH_WINDOW / 1.05f,HEIGHT_WINDOW / 1.2f }, arrow,
		[&]() ->T_Screen { return changePlayer(true); }));

	m_buttons.push_back(Btn(WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 1.1f, Resources::TEXTURE::SELECT,
		[]() ->T_Screen {return SELECT_AREA; }));
}

void SelectVehicle::creatPlayers() {
	
	m_playerName.push_back(sf::IntRect(0, 0, 1223 / 3, 123));
	m_playerName.push_back(sf::IntRect(1226 / 3, 0, 1223 / 3, 123));
	m_playerName.push_back(sf::IntRect((1226 / 3)*2, 0, 1223 / 3, 123));
}

T_Screen SelectVehicle::changePlayer(bool next) {
	if (next)
		SelectVehicle::currPlayer++;
	else {
		SelectVehicle::currPlayer--;
		if (SelectVehicle::currPlayer < player::Spike)
			SelectVehicle::currPlayer = player::Tricky;
	}
	SelectVehicle::currPlayer %= 3;
	updateRect();
	return SELECT_VEHICLE;
}

void SelectVehicle::updateRect() {
	m_names.setTextureRect(m_playerName[currPlayer]);
}

void SelectVehicle::update() {
	m_ani.update(m_gameClock.restart());
}

void SelectVehicle::draw(sf::RenderWindow& target) const {
	Draw(target);
	target.draw(m_names);
	target.draw(m_player);
}

