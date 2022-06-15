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
		P_Monster,
		P_Truck,
		P_COIN,
		P_FLAG,
		MaxPlayer,
	};

	enum TEXTURE {
		BG = 0,
		PLAY,
		HELP,
		MUTE,
		SOUND,
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
		Score,
		NEXT,
		STAR,
		HELP_CENTER1,
		HELP_CENTER2,
		CLOCK,
		EMPTY_B,
		MaxTexture,
	};

	enum  SOUNDS {
		CLICK,
		SLIDE,
		Winning,
		KnifeStab,
		Crash,
		Coins,
		UNLOCK,
		RATE,
		GAME_MUSIC,
		MaxSounds,
	};
	
	const sf::Font& getFont();
	const sf::SoundBuffer& getSound(SOUNDS );
	const sf::Texture& getTexture(TEXTURE, bool = false);
	const AnimationData& getData(Players);

private:
	std::string			m_textPath[MaxTexture] = {
						"background.png",
						"play.png",
						"help.png",
						"mute.png",
						"sound.png",
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
						"score.png",
						"next.png",
						"star.png",
						"HelpCenter1.png",
						"HelpCenter2.png",
						"clock.png",
						"emptyButton.png",
										
	};	

	std::string				m_soundsPath[MaxSounds] = {
							"coll.wav",
							"slide.wav",
							"winning.wav",
							"KnifeStab.wav",
							"crash.wav",
							"coin.wav",
							"unlock.wav",
							"star.wav",
							"gameMusic.wav",
						
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