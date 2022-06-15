#include "SelectVehicle.h"

//___________________________________________________

SelectVehicle::SelectVehicle()
	:Screen(Resources::TEXTURE::SELECTION, T_Screen::MENU),
	m_ani(Resources::instance().getData(player::Spike), Direction::Win, m_player)
{
	creatNameFrame();
	creatPlayers();
	creatPlayersName();
	createButtons();
}

//___________________________________________________

void SelectVehicle::createButtons() {

	sf::Sprite arrow;
	arrow.setTexture(Resources::instance().getTexture(Resources::TEXTURE::ARROW));
	arrow.setScale(ARROW_SCALE);

	m_buttons.push_back(Btn(LEFT_ARROW, arrow,
		[&]() ->T_Screen { return changePlayer(false); }));
	arrow.scale(MOVE_LEFT);

	m_buttons.push_back(Btn(RIGHT_ARROW, arrow,
		[&]() ->T_Screen { return changePlayer(true); }));

	m_buttons.push_back(Btn(SELECT_POS.x, SELECT_POS.y, Resources::TEXTURE::SELECT,
		[]() ->T_Screen {return SELECT_AREA; }));
}

//___________________________________________________

void SelectVehicle::creatPlayers() {

	m_player.setTexture(Resources::instance().getTexture(Resources::TEXTURE::SpikeTexture));
	m_player.setOrigin(m_player.getGlobalBounds().width / HALF, m_player.getGlobalBounds().height / HALF);
	m_player.setPosition(PLAYER_SELECTION_POS);
	m_player.setScale(PLAYER_SELECTION_SCALE);

}

//___________________________________________________

void SelectVehicle::creatNameFrame() {

	m_playerName.push_back(PLAYERS_NAME[TRICKY]);
	m_playerName.push_back(PLAYERS_NAME[SPIKE]);
	m_playerName.push_back(PLAYERS_NAME[JAKE]);
}

//___________________________________________________

void SelectVehicle::creatPlayersName() {

	m_names.setTextureRect(m_playerName[GameData::instance().getPlayer()]);
	m_names.setOrigin(m_names.getGlobalBounds().width / HALF, m_names.getGlobalBounds().height / HALF);
	m_names.setPosition(NAMES_POS);
	m_names.setTexture(Resources::instance().getTexture(Resources::TEXTURE::NAMES));
	m_names.setScale(NAMES_SCALE);

}

//___________________________________________________

T_Screen SelectVehicle::changePlayer(bool next) {
	if (next) {
		GameData::instance().chooseplayer(ADD);
		if (GameData::instance().getPlayer() > player::Jake)
			GameData::instance().setPlayer(player::Tricky);
	}
	else {
		GameData::instance().chooseplayer(-ADD);
		if (GameData::instance().getPlayer() < player::Tricky)
			GameData::instance().setPlayer(player::Jake);
	}
	updateRect();
	m_player.setTexture(Resources::instance().getTexture(static_cast<Resources::TEXTURE>(SPRITE_POS + GameData::instance().getPlayer())));
	return SELECT_VEHICLE;
}

//___________________________________________________

void SelectVehicle::updateRect() {
	m_names.setTextureRect(m_playerName[GameData::instance().getPlayer()]);
}

//___________________________________________________

void SelectVehicle::handleGame(sf::Time& delta) {
	m_ani.update(delta); 
}

//___________________________________________________

void SelectVehicle::draw(sf::RenderWindow& target) const {
	Draw(target);
	target.draw(m_names);
	target.draw(m_player);
}

