#include"PlayerVehicles.h"

PlayerVehicles::PlayerVehicles(Resources::TEXTURE texture,
	std::shared_ptr<b2World> world,
	sf::Vector2f pos,
	Resources::Players aniData
	,Resources::SOUNDS sound)
	:MovingObject(texture,world, pos,aniData,sound)
{
	CreateBody(pos);
}

void PlayerVehicles::CreateBody(sf::Vector2f pos) {

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(pos.x, pos.y);
	m_body = m_world->CreateBody(&m_bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(45, 45);
	b2FixtureDef fixtureDef;

	fixtureDef.shape	= &dynamicBox;
	fixtureDef.density	= 0.5f;
	fixtureDef.friction = 0.01f;

	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);

	setSensor(0, dynamicBox, fixtureDef, 1);
	setMassa(10.0f);
}

void PlayerVehicles::setSensor(float posX, b2PolygonShape& poly, b2FixtureDef& fixtureDef, int id) {
	poly.SetAsBox(5, 5, b2Vec2(posX, 40), 0);
	b2Fixture* m_footSensorFixture;
	fixtureDef.isSensor = true;
	m_footSensorFixture = m_body->CreateFixture(&fixtureDef);
	m_footSensorFixture->SetUserData((void*)id);
}

void PlayerVehicles::setMassa(float weight) {
	b2MassData massa;
	massa.mass = weight;
	massa.center = b2Vec2(m_body->GetLocalCenter().x, m_body->GetLocalCenter().y);
	massa.I = m_sprite.getOrigin().y;
	m_body->SetMassData(&massa);
}

void PlayerVehicles::update(sf::Time delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		jump();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		drive(40);

	b2Vec2  position = m_body->GetPosition();
	float	angle = 180 / b2_pi * m_body->GetAngle();
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(angle);
	m_animation.update(delta);
}