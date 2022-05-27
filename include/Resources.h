#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "AnimationData.h"

const int NUM_OF_TEXTURE = 8;
const int NUM_OF_MAPS = 1;


class Resources {
private:

	std::string				m_textPath[NUM_OF_TEXTURE] = {
						"GameBackround.png",
						"play.png",
						"help.png",
						"mute.png",
						"sound.png",
						"logo.png",
						"tempScateSprite.png",
						"map1.jpg",
						
	};
	std::vector<sf::Texture>		m_textures;
	sf::SoundBuffer					m_sound;

	sf::Font						m_font;
	AnimationData					m_data;

	Resources();
	Resources(const Resources&) = delete;
	void operator=(const Resources&) = delete;

	void loadTextur();

public:
	static Resources& instance();

	enum class TEXTURE {
		BG  = 0,
		PLAY ,
		HELP ,
		MUTE,
		SOUND,
		LOGO,
		SCATE,
		MAP1,
		
	};

	const sf::Font& getFont();
	const sf::SoundBuffer& getSound();
	const sf::Texture& getTexture(Resources::TEXTURE, bool repated = false);
	const AnimationData& animationData( ) { return m_data; }



};