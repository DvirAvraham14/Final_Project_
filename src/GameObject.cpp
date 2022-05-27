#include"GameObject.h"

GameObject::GameObject(const sf::Texture &texture, std::shared_ptr<b2World> world,sf::Vector2f pos)
	:m_world(world) 
{
	m_sprite.setTexture(texture);
	m_contacting = false;
	CreateBody(pos);
}

GameObject::GameObject(std::shared_ptr<b2World> world)
	:m_world(world), m_body(nullptr)
{
	m_contacting = false;
}

void GameObject::CreateBody(sf::Vector2f pos) {
	//b2BodyDef bodyDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(pos.x / SCALAR, pos.y / SCALAR);
	m_body = m_world->CreateBody(&m_bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.01f;
	fixtureDef.restitution = 0.05f;
	b2MassData massa;
	massa.mass = 10;
	massa.center = m_body->GetLocalCenter();
	m_body->SetMassData(&massa);
	// Add the shape to the body
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
}