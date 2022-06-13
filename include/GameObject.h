#pragma once
#include "macro.h"

class GameObject
{
public:
	GameObject() = default;
	GameObject(std::shared_ptr<b2World> world);
	GameObject(Resources::TEXTURE, std::shared_ptr<b2World>, sf::Vector2f pos, Resources::SOUNDS sound);
	virtual ~GameObject() { m_body->GetWorld()->DestroyBody(m_body); }
	virtual void draw(sf::RenderWindow& target) const;
	void undoCollision();

	inline sf::Sprite getSprite() { return m_sprite; }
	inline virtual void update(sf::Time) {};
	inline void startContact() { m_contacting = true; }
	inline void endContact() { m_contacting = false; }
	inline sf::Vector2f getPos() const { return m_sprite.getPosition(); }
	inline bool getContacting()const { return m_contacting; }
	inline void play() { m_sound.play(); }
	inline void stopPlay() { m_sound.stop(); }
	inline void setGravity(float gravity) { m_body->SetGravityScale(gravity); }
	inline void stopBody() { m_body->SetAwake(false); }
	inline void removeObj() { toDelete = true; }
	inline bool getDeleteStatus() { return toDelete; }
protected:
	std::shared_ptr<b2World> m_world;
	sf::Sprite				 m_sprite;
	sf::Sound				 m_sound;
	b2Body* m_body;
	bool					 m_contacting;
	bool					 toDelete = false;

private:
	virtual void CreateBody(sf::Vector2f pos) = 0;
};