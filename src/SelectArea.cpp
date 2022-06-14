#include"SelectArea.h"

//______________________________________________________
SelectArea::SelectArea()
	:Screen(Resources::TEXTURE::CITY_NIGHT, T_Screen::SELECT_VEHICLE)
{
	creatBgs();
	createButtons();

	m_names.setTexture(Resources::instance().getTexture(Resources::TEXTURE::AREAS));
	m_names.setTextureRect(m_BgName[m_currBg]);
	m_names.setOrigin(m_names.getGlobalBounds().width / 2, m_names.getGlobalBounds().height / 2);
	m_names.setPosition(WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 4.0f);
	m_names.setScale(WIDTH_WINDOW / 2222.f, WIDTH_WINDOW / 2222.f);
}

//______________________________________________________
void SelectArea::createButtons() {

	sf::Sprite arrow;
	arrow.setTexture(Resources::instance().getTexture(Resources::TEXTURE::ARROW));
	arrow.setScale(WIDTH_WINDOW / 1420.0f, WIDTH_WINDOW / 1420.0f);

	m_buttons.push_back(Btn({ WIDTH_WINDOW / 19.0f,HEIGHT_WINDOW / 2.2f }, arrow,
		[&]() ->T_Screen { if (m_currBg == 0) m_currBg = 3;  else  m_currBg--;  updateRect(); return SELECT_AREA; }));
	arrow.scale(-1, 1);

	m_buttons.push_back(Btn({ WIDTH_WINDOW / 1.05f,HEIGHT_WINDOW / 2.2f }, arrow,
		[&]() ->T_Screen {if (m_currBg == 3) m_currBg = 0; else  m_currBg++;  updateRect(); return SELECT_AREA; }));
	m_buttons.push_back(Btn(WIDTH_WINDOW / 2.0f, HEIGHT_WINDOW / 1.25f, Resources::TEXTURE::SELECT_A,
		[&]() ->T_Screen {GameData::instance().setCurrBg(Resources::TEXTURE(m_currBg + 14)); return SELECT_LEVEL; }));
}

//______________________________________________________
void SelectArea::creatBgs() {

	m_BgName.push_back(sf::IntRect(0, 0, 2500 / 4, 122));
	m_BgName.push_back(sf::IntRect(2500 / 4, 0, 2500 / 4, 122));
	m_BgName.push_back(sf::IntRect((2500 / 4) * 2, 0, 2500 / 4, 122));
	m_BgName.push_back(sf::IntRect((2500 / 4) * 3, 0, 2500 / 4, 122));
}

//______________________________________________________
void SelectArea::updateRect() {

	sf::RectangleShape rect;
	rect.setSize({ WIDTH_WINDOW, HEIGHT_WINDOW });
	rect.setTexture(&Resources::instance().getTexture(Resources::TEXTURE(m_currBg + 14)));
	m_background = rect;
	m_names.setTextureRect(m_BgName[m_currBg]);
}

//______________________________________________________
void SelectArea::draw(sf::RenderWindow& target) const {

	Draw(target);
	target.draw(m_names);
}
