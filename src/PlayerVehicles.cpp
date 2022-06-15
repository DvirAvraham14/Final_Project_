#include "PlayerVehicles.h"

//___________________________________________________

PlayerVehicles::PlayerVehicles(Resources::TEXTURE texture,
	std::shared_ptr<b2World> world,
	Resources::SOUNDS sound)
	:MovingObject(texture, world, PLAYER_POS, Resources::Players::Tricky, sound)
{
	CreateBody(PLAYER_POS);
	m_sprite.setScale(PLAYER_SCALE);
	setBox2dEnable(false);
}

//___________________________________________________

void PlayerVehicles::CreateBody(sf::Vector2f pos) {

	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(pos.x, pos.y);
	m_body = m_world->CreateBody(&m_bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(BOX_SCALE.x, BOX_SCALE.y);
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = PLAYER_DENSITY;
	fixtureDef.friction = PLAYER_FRICTION;

	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);

	setSensor(-MASS, fixtureDef, ID);//first wheel
	setSensor(MASS, fixtureDef, ID);//secound wheel
	setMassa(MASS);
}

//___________________________________________________

void PlayerVehicles::setSensor(float posX, b2FixtureDef& fixtureDef, int id) {

	b2CircleShape circle;
	circle.m_radius = RADIUS;
	circle.m_type = circle.e_circle;

	circle.m_p = b2Vec2(m_sprite.getPosition().x + posX, m_sprite.getPosition().y + CIRCLE_OFFSET);

	b2FixtureDef footSensorFixtureDef;
	footSensorFixtureDef.isSensor = true;
	footSensorFixtureDef.shape = &circle;
	footSensorFixtureDef.userData = (void*)id;
	m_body->CreateFixture(&footSensorFixtureDef);
}

//___________________________________________________

void PlayerVehicles::setMassa(float weight) {
	b2MassData massa;
	massa.mass = weight;
	massa.center = b2Vec2(m_body->GetLocalCenter().x, m_body->GetLocalCenter().y);
	massa.I = m_sprite.getOrigin().y;
	m_body->SetMassData(&massa);
}

//___________________________________________________

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

//___________________________________________________

void PlayerVehicles::updatePosition() {
	b2Vec2  position = m_body->GetPosition();
	float	angle = ANGLE / b2_pi * m_body->GetAngle();
	auto temp = std::fmod(angle, FULL_ANGLE);
	if (std::abs(temp) > MAX_ROTATION && !m_isDead) {
		m_animation.direction(Direction::FrontFall);
		angle = RESET;
		setEnableMove(false);
		m_isDead = true;
	}
	m_sprite.setRotation(angle);
	m_sprite.setPosition(position.x, position.y);
}

//___________________________________________________

void PlayerVehicles::drive(Resources::Players player) {
	if (m_contacting) {
		if (m_speed <= 0)
			m_animation.direction(Direction::Push);
		m_speed += (m_speed < MAX_SPEED[player]) ? PUSH : RESET;
		float force = physicalMove(m_body->GetLinearVelocity().x, m_speed);
		m_body->ApplyForce(b2Vec2(force, RESET), m_body->GetWorldCenter(), true);
	}
}

//___________________________________________________

void PlayerVehicles::jump(float height, Resources::Players player) {
	if (m_contacting) {
		m_body->SetLinearVelocity({ m_body->GetLinearVelocity().x,RESET });
		m_animation.direction(Direction::Filp);
		b2Vec2 vel = m_body->GetLinearVelocity();
		float force = physicalMove(vel.y, ((height == 0) ? JUMP_HEIGHT[player] : height));
		m_body->ApplyForce(b2Vec2(0, -force), m_body->GetWorldCenter(), true);
		endContact();
	}
}

//___________________________________________________

void PlayerVehicles::coilliedSpikes() {
	m_isDead = m_contacting = true;
	m_body->SetLinearVelocity({-float(PUSH), RESET });
	this->undoCollision();
	setAni(Direction::FrontFall);
}