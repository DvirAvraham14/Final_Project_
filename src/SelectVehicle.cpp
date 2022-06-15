#include"SelectVehicle.h"

SelectVehicle::SelectVehicle()
	:Screen(Resources::TEXTURE::SELECTION, T_Screen::MENU),
	m_ani(Resources::instance().getData(player::Spike), Direction::Win, m_player)
{
	creatNameFrame();
	creatPlayers();
	creatPlayersName();
	createButtons();
}

void SelectVehicle::createButtons() {

	sf::Sprite arrow;
	arrow.setTexture(Resources::instance().getTexture(Resources::TEXTURE::ARROW));
	arrow.setScale(WIDTH_WINDOW / 1420.0f, WIDTH_WINDOW / 1420.0f);

	m_buttons.push_back(Btn({ 60,HEIGHT_WINDOW / 2.2f }, arrow,
		[&]() ->T_Screen { return changePlayer(false); }));
	arrow.scale(-1, 1);

	m_buttons.push_back(Btn({ WIDTH_WINDOW - 60,HEIGHT_WINDOW / 2.2f }, arrow,
		[&]() ->T_Screen { return changePlayer(true); }));

	m_buttons.push_back(Btn(WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 1.25f, Resources::TEXTURE::SELECT,
		[]() ->T_Screen {return SELECT_AREA; }));
}

void SelectVehicle::creatPlayers() {

	m_player.setTexture(Resources::instance().getTexture(Resources::TEXTURE::SpikeTexture));
	m_player.setOrigin(m_player.getGlobalBounds().width / 2.f, m_player.getGlobalBounds().height / 2.f);
	m_player.setPosition(WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 2.5f);
	m_player.setScale(WIDTH_WINDOW / 900, WIDTH_WINDOW / 900);

}
void SelectVehicle::creatNameFrame() {

	m_playerName.push_back(sf::IntRect(0, 0, 1223 / 3, 123));
	m_playerName.push_back(sf::IntRect(1226 / 3, 0, 1223 / 3, 123));
	m_playerName.push_back(sf::IntRect((1226 / 3) * 2, 0, 1223 / 3, 123));
}

void SelectVehicle::creatPlayersName() {

	m_names.setTextureRect(m_playerName[GameData::instance().getPlayer()]);
	m_names.setOrigin(m_names.getGlobalBounds().width / 2, m_names.getGlobalBounds().height / 2);
	m_names.setPosition(WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 4.0f);
	m_names.setTexture(Resources::instance().getTexture(Resources::TEXTURE::NAMES));
	m_names.setScale(WIDTH_WINDOW / 2222.f, WIDTH_WINDOW / 2222.f);

}

T_Screen SelectVehicle::changePlayer(bool next) {
	if (next) {
		GameData::instance().chooseplayer(1);
		if (GameData::instance().getPlayer() > player::Jake)
			GameData::instance().setPlayer(player::Tricky);
	}
	else {
		GameData::instance().chooseplayer(-1);
		if (GameData::instance().getPlayer() < player::Tricky)
			GameData::instance().setPlayer(player::Jake);
	}
	updateRect();
	m_player.setTexture(Resources::instance().getTexture(static_cast<Resources::TEXTURE>(22 + GameData::instance().getPlayer())));
	return SELECT_VEHICLE;
}

void SelectVehicle::updateRect() {
	m_names.setTextureRect(m_playerName[GameData::instance().getPlayer()]);
}

void SelectVehicle::handleGame(sf::Time& delta) {
	m_ani.update(delta); 
}


void SelectVehicle::draw(sf::RenderWindow& target) const {
	Draw(target);
	target.draw(m_names);
	target.draw(m_player);
}

