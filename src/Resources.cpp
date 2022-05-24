#include <iostream>
#include "Resources.h"


Resources::Resources()
{
	if (!m_font.loadFromFile("gameFont.otf"))
		std::cerr << "Font error\n";
	//std::exception();
	if (!m_sound.loadFromFile("coll.wav"))
		std::cerr << "sound loading failed\n";
	//std::exception();

	loadTextur();
}

//__________________________________
Resources& Resources::instance()
{
	static Resources instance;
	return instance;
}

//__________________________________
const sf::Font& Resources::getFont() {
	return m_font;
}

//__________________________________
const sf::SoundBuffer& Resources::getSound() {
	return m_sound;
}


const sf::Texture& Resources::getTexture(Resources::TEXTURE sprite, bool repated) {
	auto index = static_cast<size_t>(sprite);
	m_textures[index].setRepeated(repated);
	return m_textures[index];
}

//__________________________________

void Resources::loadTextur() {
	for (auto i = 0; i < NUM_OF_TEXTURE; i++) {
		sf::Texture temp;
		temp.loadFromFile(m_textPath[i]);
		m_textures.push_back(temp);
	}
}

