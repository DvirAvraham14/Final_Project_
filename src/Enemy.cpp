#include"Enemy.h"

//___________________________________________________

Enemy::Enemy(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::Players aniData, Resources::SOUNDS sound)
	:MovingObject(texture, world, pos, aniData, sound)
{
	CreateBody(pos);
}

//___________________________________________________

void Enemy::CreateBody(sf::Vector2f pos) {

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(pos.x, pos.y);
	m_body = m_world->CreateBody(&m_bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_sprite.getTextureRect().width / HALF,
		m_sprite.getTextureRect().height / 2);
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = ENEMY_DENSITY;
	fixtureDef.friction = ENEMY_FRICTION;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
}