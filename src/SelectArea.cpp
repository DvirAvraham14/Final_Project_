#include"SelectArea.h"

//___________________________________________________

SelectArea::SelectArea()
	:Screen(Resources::TEXTURE::CITY_NIGHT, T_Screen::SELECT_VEHICLE)
{
	creatBgs();
	createButtons();

	m_names.setTexture(Resources::instance().getTexture(Resources::TEXTURE::AREAS));
	m_names.setTextureRect(m_BgName[m_currBg]);
	m_names.setOrigin(m_names.getGlobalBounds().width / HALF, m_names.getGlobalBounds().height / HALF);
	m_names.setPosition(NAMES_POS);
	m_names.setScale(NAMES_SCALE);
}

//___________________________________________________

void SelectArea::createButtons() {

	sf::Sprite arrow;
	arrow.setTexture(Resources::instance().getTexture(Resources::TEXTURE::ARROW));
	arrow.setScale(ARROW_SCALE);

	m_buttons.push_back(Btn(LEFT_ARROW, arrow,
		[&]() ->T_Screen { if (m_currBg == NIGHT_CITY_BG) m_currBg = BEACH_BG;  else  m_currBg--;  updateRect(); return SELECT_AREA; }));
	arrow.scale(MOVE_LEFT);

	m_buttons.push_back(Btn(RIGHT_ARROW, arrow,
		[&]() ->T_Screen {if (m_currBg == BEACH_BG) m_currBg = NIGHT_CITY_BG; else  m_currBg++;  updateRect(); return SELECT_AREA; }));
	m_buttons.push_back(Btn(SELECT_POS.x, SELECT_POS.y, Resources::TEXTURE::SELECT_A,
		[&]() ->T_Screen {GameData::instance().setCurrBg(Resources::TEXTURE(m_currBg + SPRITE_AREA_POS)); return SELECT_LEVEL; }));
}

//___________________________________________________

void SelectArea::creatBgs() {

	m_BgName.push_back(AREA_NAME[NIGHT_CITY_BG]);
	m_BgName.push_back(AREA_NAME[SNOW_BG]);
	m_BgName.push_back(AREA_NAME[CITY_BG]);
	m_BgName.push_back(AREA_NAME[BEACH_BG]);
}

//___________________________________________________

void SelectArea::updateRect() {

	sf::RectangleShape rect;
	rect.setSize({ WIDTH_WINDOW, HEIGHT_WINDOW });
	rect.setTexture(&Resources::instance().getTexture(Resources::TEXTURE(m_currBg + SPRITE_AREA_POS)));
	m_background = rect;
	m_names.setTextureRect(m_BgName[m_currBg]);
}

//___________________________________________________

void SelectArea::draw(sf::RenderWindow& target) const {

	Draw(target);
	target.draw(m_names);
}
