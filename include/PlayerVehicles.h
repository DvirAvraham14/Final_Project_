#pragma once
#include "MovingObject.h"
class PlayerVehicles : public MovingObject
{
public:

	PlayerVehicles(Resources::TEXTURE, std::shared_ptr<b2World>, Resources::SOUNDS sound);
	virtual void drive(Resources::Players = Resources::Players::MaxPlayer);
	virtual void jump(float height = 0, Resources::Players player = Resources::Players::MaxPlayer);
	virtual void update(sf::Time delta);
	virtual void CreateBody(sf::Vector2f pos);
	void coilliedSpikes();
	bool getCollideStatus() const { return m_body->GetFixtureList()->IsSensor(); }
	bool isDead() const { return m_isDead; }
private:
	void setSensor(float posXm, b2FixtureDef&, int id);
	void setMassa(float);
	void updatePosition();
	void stop() {

		if (m_contacting) {
			m_speed -= (m_speed > 1) ? 0.1f : 0;
			/*if (m_speed < 0)
				m_speed += 0.5f;
			else
				m_enableMove = true;*/
			float force = physicalMove(m_body->GetLinearVelocity().x, m_speed);
			m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(), true);
		}
	}
	bool m_isDead = false;
};