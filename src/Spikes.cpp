#include "Spikes.h"

//___________________________________________________

Spikes::Spikes(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::SOUNDS sound,bool )
	:Obstacles(texture, world, pos, sound)
{
	//CreateBody(pos);
}

//___________________________________________________

void Spikes::CreateBody(sf::Vector2f pos) {

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(pos.x, pos.y - m_sprite.getOrigin().y);
	m_body = m_world->CreateBody(&m_bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_sprite.getTexture()->getSize().x / HALF,
		m_sprite.getTexture()->getSize().y / HALF);
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = SPIKES_DENSITY;
	fixtureDef.friction = SPIKES_FRICTION;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
	setSensor(RESET, dynamicBox, fixtureDef, ID);
}

//___________________________________________________

void Spikes::setSensor(float posX, b2PolygonShape& poly, b2FixtureDef& fixtureDef, int id) {

	poly.SetAsBox(PUSH, PUSH, b2Vec2(posX, SPIKES_BOX), RESET);
	poly.SetAsBox(m_sprite.getGlobalBounds().width / HALF, m_sprite.getGlobalBounds().height / HALF, b2Vec2(RESET, -HALF * m_sprite.getOrigin().y), RESET);
	b2Fixture* m_footSensorFixture;
	fixtureDef.isSensor = true;
	m_footSensorFixture = m_body->CreateFixture(&fixtureDef);
	m_footSensorFixture->SetUserData((void*)ID);
}