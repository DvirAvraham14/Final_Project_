#include"Enemy.h"
Enemy::Enemy(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos, Resources::Players aniData)
	:MovingObject(texture, world, pos, aniData)
{
	CreateBody(pos);
}

void Enemy::CreateBody(sf::Vector2f pos) {

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(pos.x, pos.y);
	m_body = m_world->CreateBody(&m_bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_sprite.getTexture()->getSize().x / 2,
		m_sprite.getTexture()->getSize().y / 2);
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.f;

	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
}
void Enemy::checkAndGo(sf::Time time) {
	//if(fmod(time.asSeconds(),5)<=4 )
		drive(7);
}