#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "AnimationData.h"

class Resources {
public:
	static Resources& instance();

	enum Players {
		Spike,
		Enemy,
		MaxPlayer,
	};

	enum TEXTURE {
		BG = 0,
		PLAY,
		HELP,
		MUTE,
		SOUND,
		LOGO,
		SCATE,
		RAILING,
		SPIKES,
		SpikeTexture,
		Monster,
		Flag,
		MAP1,
		MaxTexture,
	};

	enum  SOUNDS {
		CLICK,
		SLIDE,
		LANDING,
		Winning,
		MaxSounds,
	};

	const sf::Font& getFont();
	const sf::SoundBuffer& getSound(SOUNDS );
	const sf::Texture& getTexture(TEXTURE, bool = false);
	const AnimationData& getData(Players);
private:
	std::string				m_textPath[MaxTexture] = {
						"GameBackround.png",
						"play.png",
						"help.png",
						"mute.png",
						"sound.png",
						"logo.png",
						"tempScateSprite.png",
						"railing.png",
						"spikes.png",
						"Charchater1.png",
						"tempMonster.png",
						"Flag.png",
						"map1.jpg",				
	};	

	std::string				m_soundsPath[MaxSounds] = {
							"coll.wav",
							"slide.wav",
							"landing.wav",
							"winning.wav",
						
	};

	std::vector<sf::Texture>		m_textures;
	std::vector<sf::SoundBuffer>	m_sounds;
	std::vector<AnimationData>		m_animaData;
	sf::Font						m_font;


	Resources();
	Resources(const Resources&) = delete;
	void operator=(const Resources&) = delete;

	void loadTextur();
	void loadSounds();
	void loadAnimaData();

};