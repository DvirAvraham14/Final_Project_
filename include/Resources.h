#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "AnimationData.h"

class Resources {
public:
	static Resources& instance();
	
	enum Players {
		Tricky,
		Spike,
		Jake,
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
		TrickyTexture,
		SpikeTexture,
		JackTexture,
		Monster,
		Flag,
		Truck,
		Coin,
		MaxTexture,
	};

	enum  SOUNDS {
		CLICK,
		SLIDE,
		Winning,
		KnifeStab,
		Crash,
		Coins,
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
						"Tricky.png",
						"Spike.png",
						"jake.png",
						"Monster.png",
						"Flag.png",
						"truck.png",
						"coin.png",
										
	};	

	std::string				m_soundsPath[MaxSounds] = {
							"coll.wav",
							"slide.wav",
							"winning.wav",
							"KnifeStab.wav",
							"crash.wav",
							"coin.wav",
						
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