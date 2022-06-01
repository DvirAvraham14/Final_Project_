#include <iostream>
#include "Resources.h"


Resources::Resources()
{

	if (!m_font.loadFromFile("gameFont.otf"))
		std::cerr << "Font error\n";

	loadTextur();
	loadSounds();
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

const sf::Texture& Resources::getTexture(Resources::TEXTURE sprite, bool repated) {
	auto index = static_cast<size_t>(sprite);
	m_textures[index].setRepeated(repated);
	return m_textures[index];
}
//__________________________________

const sf::SoundBuffer& Resources::getSound(Resources::SOUND sound) {
	auto index = static_cast<size_t>(sound);
	return m_sounds[index];
}

//__________________________________

void Resources::loadTextur() {
	for (auto i = 0; i < NUM_OF_TEXTURE; i++) {
		sf::Texture temp;
		temp.loadFromFile(m_textPath[i]);
		m_textures.push_back(temp);
	}
}

//__________________________________

void Resources::loadSounds() {

	for (auto i = 0; i < NUM_OF_SOUND; i++) {
		sf::SoundBuffer temp;
		temp.loadFromFile(m_soundsPath[i]);
		m_sounds.push_back(temp);
	}
}

