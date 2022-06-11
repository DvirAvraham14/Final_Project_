#pragma once
#include "macro.h"

class GameObject
{
public:
	GameObject() =default;
	GameObject(std::shared_ptr<b2World> world);
	/*GameObject(const sf::Texture &texture, std::shared_ptr<b2World>,sf::Vector2f pos);*/
	GameObject(Resources::TEXTURE, std::shared_ptr<b2World>,sf::Vector2f pos, Resources::SOUNDS sound);
	virtual ~GameObject() { m_body->GetWorld()->DestroyBody(m_body); }
	sf::Sprite getSprite() { return m_sprite; }
	virtual void draw(sf::RenderWindow& target) const;
	virtual void update(sf::Time) {};

	void startContact() { m_contacting = true; }
	void endContact() { m_contacting = false; }

	sf::Vector2f getPos() const{ return m_sprite.getPosition(); }
	bool getContacting()const { return m_contacting; }

	void play() {/*if(m_sound.getStatus()!=sf::Sound::Playing)*/ m_sound.play(); }
	void stopPlay() {m_sound.stop(); }

	void undoCollision() {
		for (auto it = m_body->GetFixtureList(); it; it = it->GetNext()) {
			if (it)
				it->SetSensor(true);
		}
	}

	void setGravity(float gravity) { m_body->SetGravityScale(gravity); }
	void stopBody() { m_body->SetAwake(false); }
	void removeObj() {
		toDelete = true;
	}

	bool getDeleteStatus() { return toDelete; }
protected:
	std::shared_ptr<b2World> m_world;
	sf::Sprite				 m_sprite;
	sf::Sound				 m_sound;
	b2Body*					 m_body;
	bool					 m_contacting;
	bool					 toDelete = false;

private:
	virtual void CreateBody(sf::Vector2f pos) = 0;
};