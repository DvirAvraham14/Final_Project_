#include"GameObject.h"
GameObject::GameObject(sf::Texture texture, std::shared_ptr<b2World> world)
:m_world(world) {
	sf::Sprite s;
	m_texture = texture;
	s.setTexture(m_texture);
	m_sprite = s;
	CreateBody();
}

void GameObject::CreateBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f / SCALAR, 500.0f / SCALAR);
	m_body = m_world->CreateBody(&bodyDef);
	// Define another box shape for our dynamic body
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	// Define the dynamic body fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	// Set the box density to be non-zero, so it will be dynamic
	fixtureDef.density = 1.0f;

	// Override the default friction
	fixtureDef.friction = 0.3f;//לסובב אובייקט

	// Add the shape to the body
	m_body->CreateFixture(&fixtureDef);
}