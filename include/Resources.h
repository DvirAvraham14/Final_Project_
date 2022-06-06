#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "AnimationData.h"

class Resources {
public:
	static Resources& instance();
	
	enum Players {
		Spike,
		Jake,
		Tricky,
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
		ROAD,
		MAP_ROAD,
		LOCK,
		SELECTION,
		ARROW,
		SELECT,
		NAMES,
		BACK,
		CITY_NIGHT,
		SNOWY_CITY,
		CITY,
		BEACH,
		AREAS,
		SELECT_A,
		RAILING,
		SPIKES,
		SpikeTexture,
		Monster,
		Flag,
		Truck,
		MaxTexture,
	};

	enum  SOUNDS {
		CLICK,
		SLIDE,
		LANDING,
		Winning,
		KnifeStab,
		Crash,
		MaxSounds,
	};

	const sf::Font& getFont();
	const sf::SoundBuffer& getSound(SOUNDS );
	const sf::Texture& getTexture(TEXTURE, bool = false);
	const AnimationData& getData(Players);
private:
	std::string				m_textPath[MaxTexture] = {
						"background.png",
						"play.png",
						"help.png",
						"mute.png",
						"sound.png",
						"logo.png",
						"road.png",
						"roadMap.png",
						"lock.png",
						"selectionV.png",
						"arrow-left.png",
						"selectB.png",
						"players.png",
						"back.png",
						"CityNight.png",
						"SnowyCity.png",
						"City.png",
						"Beach.png",
						"areas.png",
						"selectArea.png",
						"railing.png",
						"spikes.png",
						"Charchater1.png",
						"tempMonster.png",
						"Flag.png",
						"truck.png",
										
	};	

	std::string				m_soundsPath[MaxSounds] = {
							"coll.wav",
							"slide.wav",
							"landing.wav",
							"winning.wav",
							"KnifeStab.wav",
							"crash.wav",
						
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