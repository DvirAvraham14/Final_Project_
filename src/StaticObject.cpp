#include "StaticObject.h"

StaticObject::StaticObject(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::SOUNDS sound,bool collide)
	:GameObject(texture, world, pos,sound)
{
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2,
					   m_sprite.getTextureRect().height / 2);
	m_sprite.setPosition(sf::Vector2f(pos.x,pos.y-m_sprite.getOrigin().y));
	CreateBody(pos);
	if(!collide)
		undoCollision();
}

StaticObject::StaticObject( std::shared_ptr<b2World> world, Resources::TEXTURE texture, sf::Vector2f pos, Resources::SOUNDS sound)
	:GameObject(texture, world, pos, sound)
{
}

void StaticObject::CreateBody(sf::Vector2f pos) {

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(pos.x, pos.y - m_sprite.getOrigin().y);
	m_body = m_world->CreateBody(&m_bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_sprite.getTextureRect().width/2, m_sprite.getTextureRect().height / 2);
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;

	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);

}