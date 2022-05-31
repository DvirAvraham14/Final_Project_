#include"GameObject.h"

GameObject::GameObject(const sf::Texture &texture, std::shared_ptr<b2World> world,sf::Vector2f pos)
	:m_world(world) 
{
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2,
					   m_sprite.getGlobalBounds().height / 2);
	m_contacting = false;
	CreateBody(pos);
}

GameObject::GameObject(std::shared_ptr<b2World> world)
	:m_world(world), m_body(nullptr)
{
	m_contacting = false;
}
	
void GameObject::CreateBody(sf::Vector2f pos) {
	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(pos.x , pos.y );
	m_body = m_world->CreateBody(&m_bodyDef);
	
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_sprite.getTexture()->getSize().x/2, 
		m_sprite.getTexture()->getSize().y / 2);
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density		=	 0.5f;
	fixtureDef.friction		=	 0.01f;

	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);

	setSensor(0, dynamicBox, fixtureDef,  1);
	setMassa(10.0f);
}

void GameObject::setSensor(float posX, b2PolygonShape &poly, b2FixtureDef & fixtureDef, int id) {
	poly.SetAsBox(5, 5, b2Vec2(posX, m_sprite.getOrigin().y), 0);
	b2Fixture* m_footSensorFixture;
	fixtureDef.isSensor = true;
	m_footSensorFixture = m_body->CreateFixture(&fixtureDef);
	m_footSensorFixture->SetUserData((void*)id);
}
void GameObject::setMassa(float weight) {
	b2MassData massa;
	massa.mass		= weight;
	massa.center	= b2Vec2(m_body->GetLocalCenter().x, m_body->GetLocalCenter().y);
	massa.I			= m_sprite.getOrigin().y;
	m_body->SetMassData(&massa);
}

