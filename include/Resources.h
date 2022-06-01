#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "AnimationData.h"

const int NUM_OF_TEXTURE = 10;
const int NUM_OF_SOUND = 3;


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
						"railing.png",
						"spikes.png",
						"map1.jpg",
						
	};	
	std::string				m_soundsPath[NUM_OF_SOUND] = {
							"coll.wav",
							"slide.wav",
							"landing.wav",
						
	};
	std::vector<sf::Texture>		m_textures;
	std::vector<sf::SoundBuffer>	m_sounds;

	sf::Font						m_font;
	AnimationData					m_data;

	Resources();
	Resources(const Resources&) = delete;
	void operator=(const Resources&) = delete;

	void loadTextur();
	void loadSounds();

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
		RAILING,
		SPIKES,
		MAP1,
	};

	enum class SOUND {
		CLICK,
		SLIDE,
		LANDING,
	};

	const sf::Font& getFont();
	const sf::SoundBuffer& getSound(Resources::SOUND sound);
	const sf::Texture& getTexture(Resources::TEXTURE, bool repated = false);
	const AnimationData& animationData( ) { return m_data; }



};