#include"PlayerVehicles.h"

PlayerVehicles::PlayerVehicles(Resources::TEXTURE texture,
	std::shared_ptr<b2World> world,
	sf::Vector2f pos,
	Resources::Players aniData)
	:MovingObject(texture,world, pos,aniData)
{
	CreateBody(pos);
	m_sound.setBuffer(Resources::instance().getSound(Resources::SOUNDS::LANDING));
}

void PlayerVehicles::CreateBody(sf::Vector2f pos) {

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(pos.x, pos.y);
	m_body = m_world->CreateBody(&m_bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(40, 40);
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