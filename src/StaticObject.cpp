#include"StaticObject.h"

StaticObject::StaticObject(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos)
	:GameObject(texture, world, pos)
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2,
					   m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(sf::Vector2f(pos.x,pos.y-m_sprite.getOrigin().y));
	CreateBody(pos);
	m_sound.setBuffer(Resources::instance().getSound(Resources::SOUNDS::SLIDE));
}

void StaticObject::CreateBody(sf::Vector2f pos) {

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(pos.x, pos.y - m_sprite.getOrigin().y);
	m_body = m_world->CreateBody(&m_bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_sprite.getTexture()->getSize().x / 2,
		m_sprite.getTexture()->getSize().y / 2);
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.01f;
	//fixtureDef.restitution = 0.3f;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);

	//setSensor(0, dynamicBox, fixtureDef, 1);
}