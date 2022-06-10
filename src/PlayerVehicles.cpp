#include "PlayerVehicles.h"

PlayerVehicles::PlayerVehicles(Resources::TEXTURE texture,
	std::shared_ptr<b2World> world,
	Resources::SOUNDS sound)
	:MovingObject(texture, world, sf::Vector2f(6700, 450), Resources::Players::Tricky, sound)
{
	CreateBody(sf::Vector2f(6700, 450));
	setBox2dEnable(false);
}

void PlayerVehicles::CreateBody(sf::Vector2f pos) {

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(pos.x, pos.y);
	m_body = m_world->CreateBody(&m_bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(WIDTH_WINDOW / 33.3f, WIDTH_WINDOW / 23.5f);
	b2FixtureDef fixtureDef;

	fixtureDef.shape	= &dynamicBox;
	fixtureDef.density	= 0.5f;
	fixtureDef.friction = 0.1f;


	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);

	setSensor(0, dynamicBox, fixtureDef, 1);
	setMassa(10.0f);
}

void PlayerVehicles::setSensor(float posX, b2PolygonShape& poly, b2FixtureDef& fixtureDef, int id) {
	poly.SetAsBox(5, 5, b2Vec2(posX, WIDTH_WINDOW / 23.5f), 0);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_enableMove)
		jump();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_enableMove)
		drive();
	if (!m_enableMove)
		stop();

	updatePosition();
	m_animation.update(delta);
}

void PlayerVehicles::updatePosition() {
	b2Vec2  position = m_body->GetPosition();
	float	angle = 180 / b2_pi * m_body->GetAngle();
	auto temp = std::fmod(angle, 360);
	if (temp > 45) {
		m_animation.direction(Direction::FrontFall);
		angle = 0;
	}
	else if (temp < -45) {
		m_animation.direction(Direction::FallBack);
		angle = 0;
	}
	m_sprite.setRotation(angle);
	m_sprite.setPosition(position.x, position.y);
}

void PlayerVehicles::drive(Resources::Players player) {
	if (m_contacting) {
		m_speed += (m_speed < MAX_SPEED[player]) ? 5 : 0;
		float force = physicalMove(m_body->GetLinearVelocity().x, m_speed);
		m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(), true);
	}
}

void PlayerVehicles::jump(float height,Resources::Players player) {
	if (m_contacting) {
		m_animation.direction(Direction::Filp);
		b2Vec2 vel = m_body->GetLinearVelocity();
		float force = physicalMove(vel.y, ((height == 0) ? JUMP_HEIGHT[player] : height));
		m_body->ApplyForce(b2Vec2(0, -force), m_body->GetWorldCenter(), true);
		endContact();
	}
}