#include <iostream>
#include "Resources.h"
#include <format>

namespace
{
    AnimationData SpikeData()
    {
        const auto size = sf::Vector2i(250, 196);
        const auto middleSpace = sf::Vector2i(55, 142);

        auto Spike = AnimationData{};
        auto currentStart = sf::Vector2i(0, 0);
        auto nextStart = [&]()
        {
			currentStart.x += (250);
			if (currentStart.x == 250 * 11) {
			
				currentStart.x = 0;
				currentStart.y += 196;
			}
				
            return currentStart;
        };

		Spike.m_data[Direction::Win].emplace_back(currentStart, size);
		for (auto i = 1; i <= 11; i++) 
			Spike.m_data[Direction::Win].emplace_back(nextStart(), size);

		Spike.m_data[Direction::Drive].emplace_back(currentStart, size);
		for (auto i = 1; i <= 11; i++)
			Spike.m_data[Direction::Drive].emplace_back(nextStart(), size);

		Spike.m_data[Direction::Filp].emplace_back(currentStart, size);
		for (auto i = 1; i <= 11; i++)
			Spike.m_data[Direction::Filp].emplace_back(nextStart(), size);

		Spike.m_data[Direction::Push].emplace_back(currentStart, size);
		for (auto i = 1; i <= 11; i++)
			Spike.m_data[Direction::Push].emplace_back(nextStart(), size);

		Spike.m_data[Direction::FrontFall].emplace_back(currentStart, size);
		for (auto i = 1; i <= 11; i++)
			Spike.m_data[Direction::FrontFall].emplace_back(nextStart(), size);

		Spike.m_data[Direction::Start].emplace_back(currentStart, size);
		for (auto i = 1; i <= 11; i++)
			Spike.m_data[Direction::Start].emplace_back(nextStart(), size);

		Spike.m_data[Direction::Stand].emplace_back(currentStart, size);
		for (auto i = 1; i <= 11; i++)
			Spike.m_data[Direction::Stand].emplace_back(nextStart(), size);

		Spike.m_data[Direction::FallBack].emplace_back(currentStart, size);
		for (auto i = 1; i <= 11; i++)
			Spike.m_data[Direction::FallBack].emplace_back(nextStart(), size);
		
        return Spike;
    }

	AnimationData EnemyData() {
		auto enemy = AnimationData{};
		enemy.m_data[Direction::Win].emplace_back(0,0, 70,50);
		return enemy;
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
	m_animaData[Spike] = SpikeData();
	m_animaData[Enemy] = EnemyData();
}

