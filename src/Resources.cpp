#include <iostream>
#include "Resources.h"
#include <format>

const unsigned int RESET = 0;
const unsigned int POS = 1;
const unsigned int SKATE_WIDTH = 333;
const unsigned int SKATE_HEIGHT = 264;
const unsigned int MAX_SKATE_ANIMATION = 18;

const unsigned int ENEMY_WIDTH = 70;
const unsigned int ENEMY_HEIGHT = 48;
const unsigned int MAX_ENEMY_ANIMATION = 3;

const unsigned int COIN_WIDTH = 50;
const unsigned int ANIMATION_ROW = 2;
const unsigned int MAX_COIN_ANIMATION = 5;

const unsigned int TRUCK_WIDTH = 135;
const unsigned int TRUCK_HEIGHT = 90;
const unsigned int MAX_TRUCK_ANIMATION = 4;

const unsigned int FLAG_WIDTH = 80;
const unsigned int FLAG_HEIGHT = 100;
const unsigned int MAX_FLAG_ANIMATION = 10;

//___________________________________________________

namespace
{
	AnimationData SkateData()
	{
		const auto size = sf::Vector2i(SKATE_WIDTH, SKATE_HEIGHT);

		auto Spike = AnimationData{};
		auto currentStart = sf::Vector2i(RESET, RESET);
		auto nextStart = [&]()
		{
			currentStart.x += (SKATE_WIDTH);
			if (currentStart.x > SKATE_WIDTH * MAX_SKATE_ANIMATION) {

				currentStart.x = RESET;
				currentStart.y += SKATE_HEIGHT;
			}

			return currentStart;
		};

		Spike.m_data[Direction::Win].emplace_back(currentStart, size);
		for (auto i = POS; i <= MAX_SKATE_ANIMATION; i++)
			Spike.m_data[Direction::Win].emplace_back(nextStart(), size);

		for (auto i = POS; i < Direction::MaxDir; i++)
			for (auto j = 0; j < MAX_SKATE_ANIMATION; j++)
				Spike.m_data[static_cast<Direction>(i)].emplace_back(nextStart(), size);

		return Spike;
	}

	AnimationData EnemyData() {
		auto enemy = AnimationData{};
		for (auto i = 0; i < Direction::MaxDir; i++)
			for (auto rect = 0; rect < MAX_ENEMY_ANIMATION; rect++)
				enemy.m_data[static_cast<Direction>(i)].emplace_back(ENEMY_WIDTH * rect, 0, 
					ENEMY_WIDTH, ENEMY_HEIGHT);
		return enemy;
	}

	AnimationData CoinData() {
		auto coin = AnimationData{};
		for (auto i = 0; i < Direction::MaxDir; i++)
			for(auto row = 0; row < ANIMATION_ROW; row++)
				for (auto col = 0; col < MAX_COIN_ANIMATION; col++)
					coin.m_data[static_cast<Direction>(i)].emplace_back(COIN_WIDTH * col, 
						COIN_WIDTH * row, COIN_WIDTH, COIN_WIDTH);
		return coin;
	}

	AnimationData TruckData() {
		auto truck = AnimationData{};
		for (auto i = 0; i < Direction::MaxDir; i++)
			for (auto row = 0; row < ANIMATION_ROW; row++)
				for (auto col = 0; col < MAX_TRUCK_ANIMATION; col++)
					truck.m_data[static_cast<Direction>(i)].emplace_back(TRUCK_WIDTH * col, 
						TRUCK_HEIGHT * row, TRUCK_WIDTH, TRUCK_HEIGHT);
		return truck;
	}

	AnimationData FlagData() {
		auto flag = AnimationData{};
		for (auto i = 0; i < Direction::MaxDir; i++)
				for (auto col = 0; col < 10; col++)
					flag.m_data[static_cast<Direction>(i)].emplace_back(FLAG_WIDTH * col, 
						0, FLAG_WIDTH, FLAG_HEIGHT);
		return flag;
	}
}

//___________________________________________________

Resources::Resources()
	:m_textures(MaxTexture),
	m_sounds(MaxSounds),
	m_animaData(MaxPlayer)
{

	if (!m_font.loadFromFile("gameFont.TTf"))
		throw "Font error\n";

	loadTextur();
	loadSounds();
	loadAnimaData();
}

//___________________________________________________

Resources& Resources::instance()
{
	static Resources instance;
	return instance;
}

//___________________________________________________

const sf::Font& Resources::getFont() {
	return m_font;
}

//___________________________________________________

const sf::Texture& Resources::getTexture(TEXTURE index, bool repated) {
	m_textures[index].setRepeated(repated);
	return m_textures[index];
}

//___________________________________________________

const sf::SoundBuffer& Resources::getSound(SOUNDS index) {
	return m_sounds[index];
}

//___________________________________________________

const AnimationData& Resources::getData(Players index) {
	return m_animaData[index];
}

//___________________________________________________

void Resources::loadTextur() {
	for (auto i = 0; i < MaxTexture; i++)
		m_textures[i].loadFromFile(m_textPath[i]);
}

//___________________________________________________

void Resources::loadSounds() {
	for (auto i = 0; i < MaxSounds; i++)
		m_sounds[i].loadFromFile(m_soundsPath[i]);
}

//___________________________________________________

void Resources::loadAnimaData() {
	m_animaData[Tricky]		= m_animaData[Jake] = m_animaData[Spike] = SkateData();
	m_animaData[P_Monster]	= EnemyData();
	m_animaData[P_COIN]		= CoinData();
	m_animaData[P_Truck]	= TruckData();
	m_animaData[P_FLAG]     = FlagData();
}

