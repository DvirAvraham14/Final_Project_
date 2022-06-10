#include "Spikes.h"

Spikes::Spikes(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::SOUNDS sound,bool )
	:Obstacles(texture, world, pos, sound)
{
	CreateBody(pos);
}


void Spikes::CreateBody(sf::Vector2f pos) {

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(pos.x, pos.y - m_sprite.getOrigin().y);
	m_body = m_world->CreateBody(&m_bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_sprite.getTexture()->getSize().x / 2,
		m_sprite.getTexture()->getSize().y / 2 );
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.1f;
	//fixtureDef.restitution = 0.3f;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
	setSensor(0, dynamicBox, fixtureDef, 1);
}

void Spikes::setSensor(float posX, b2PolygonShape& poly, b2FixtureDef& fixtureDef, int id) {

	poly.SetAsBox(5, 5, b2Vec2(posX, WIDTH_WINDOW / 23.5f), 0);
	poly.SetAsBox(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2, b2Vec2(0, -2 * m_sprite.getOrigin().y), 0);
	b2Fixture* m_footSensorFixture;
	fixtureDef.isSensor = true;
	m_footSensorFixture = m_body->CreateFixture(&fixtureDef);
	m_footSensorFixture->SetUserData((void*)1);
}