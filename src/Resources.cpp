#include <iostream>
#include "Resources.h"
#include <format>

namespace
{
	AnimationData SpikeData()
	{
		const auto size = sf::Vector2i(333, 264);

		auto Spike = AnimationData{};
		auto currentStart = sf::Vector2i(0, 0);
		auto nextStart = [&]()
		{
			currentStart.x += (333);
			if (currentStart.x > 333 * 18) {

				currentStart.x = 0;
				currentStart.y += 264;
			}

			return currentStart;
		};

		Spike.m_data[Direction::Win].emplace_back(currentStart, size);
		for (auto i = 1; i <= 18; i++)
			Spike.m_data[Direction::Win].emplace_back(nextStart(), size);

		for (auto i = 1; i < Direction::MaxDir; i++)
			for (auto j = 0; j < 19; j++)
				Spike.m_data[static_cast<Direction>(i)].emplace_back(nextStart(), size);

		return Spike;
	}

	AnimationData EnemyData() {
		auto enemy = AnimationData{};
		for (auto i = 0; i < Direction::MaxDir; i++)
			for (auto rect = 0; rect < 3; rect++)
				enemy.m_data[static_cast<Direction>(i)].emplace_back(50 * rect, 0, 50, 48);
		return enemy;
	}

	AnimationData CoinData() {
		auto coin = AnimationData{};
		for (auto i = 0; i < Direction::MaxDir; i++)
			for(auto row = 0; row < 2 ; row++)
				for (auto col = 0; col < 5; col++)
					coin.m_data[static_cast<Direction>(i)].emplace_back(50 * col, 50* row, 50, 50);
		return coin;
	}

	AnimationData TruckData() {
		auto coin = AnimationData{};
		for (auto i = 0; i < Direction::MaxDir; i++)
			for (auto row = 0; row < 2; row++)
				for (auto col = 0; col < 4; col++)
					coin.m_data[static_cast<Direction>(i)].emplace_back(135 * col, 90 * row, 135, 90);
		return coin;
	}
}

Resources::Resources()
	:m_textures(MaxTexture),
	m_sounds(MaxSounds),
	m_animaData(MaxPlayer)
{

	if (!m_font.loadFromFile("gameFont.otf"))
		throw "Font error\n";

	loadTextur();
	loadSounds();
	loadAnimaData();
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
const sf::Texture& Resources::getTexture(TEXTURE index, bool repated) {
	m_textures[index].setRepeated(repated);
	return m_textures[index];
}

//__________________________________
const sf::SoundBuffer& Resources::getSound(SOUNDS index) {
	return m_sounds[index];
}
//__________________________________
const AnimationData& Resources::getData(Players index) {
	return m_animaData[index];
}

//__________________________________
void Resources::loadTextur() {
	for (auto i = 0; i < MaxTexture; i++)
		m_textures[i].loadFromFile(m_textPath[i]);
}

//__________________________________
void Resources::loadSounds() {
	for (auto i = 0; i < MaxSounds; i++)
		m_sounds[i].loadFromFile(m_soundsPath[i]);
}

//__________________________________
void Resources::loadAnimaData() {
	m_animaData[Tricky]		= m_animaData[Jake] = m_animaData[Spike] = SpikeData();
	m_animaData[P_Monster]	= EnemyData();
	m_animaData[P_COIN]		= CoinData();
	m_animaData[P_Truck]	= TruckData();
}

