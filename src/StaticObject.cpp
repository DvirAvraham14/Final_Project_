#include "StaticObject.h"

//___________________________________________________

StaticObject::StaticObject(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::SOUNDS sound,bool collide)
	:GameObject(texture, world, pos,sound)
{
	m_sprite.setOrigin(m_sprite.getTextureRect().width / HALF,
					   m_sprite.getTextureRect().height / HALF);
	m_sprite.setPosition(sf::Vector2f(pos.x,pos.y-m_sprite.getOrigin().y));
	CreateBody(pos);
	if(!collide)
		undoCollision();
}

//___________________________________________________

StaticObject::StaticObject( std::shared_ptr<b2World> world, Resources::TEXTURE texture, sf::Vector2f pos, Resources::SOUNDS sound)
	:GameObject(texture, world, pos, sound)
{
}

//___________________________________________________

void StaticObject::CreateBody(sf::Vector2f pos) {

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(pos.x, pos.y - m_sprite.getOrigin().y);
	m_body = m_world->CreateBody(&m_bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_sprite.getTextureRect().width/2, m_sprite.getTextureRect().height / HALF);
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = PLAYER_DENSITY;
	fixtureDef.friction = PLAYER_FRICTION;

	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
}