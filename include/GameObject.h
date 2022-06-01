#pragma once
#include "macro.h"

class GameObject
{
public:
	GameObject() =default;
	GameObject(std::shared_ptr<b2World> world);
	GameObject(const sf::Texture &texture, std::shared_ptr<b2World>,sf::Vector2f pos);
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow& target) const;
	sf::Vector2f getPos() const{ return m_sprite.getPosition(); }
	void startContact() { m_contacting = true; }
	void endContact() { m_contacting = false; }
	void play() {if(m_sound.getStatus()!=sf::Sound::Playing) m_sound.play(); }
	void stopPlay() {m_sound.stop(); }
	bool getContacting()const { return m_contacting; }
protected:
	std::shared_ptr<b2World> m_world;
	sf::Sprite				 m_sprite;
	sf::Sound				 m_sound;
	b2Body*					 m_body;
	bool m_contacting;

private:
	virtual void CreateBody(sf::Vector2f pos) = 0;
};