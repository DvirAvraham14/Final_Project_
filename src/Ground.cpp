#include "Ground.h"

//------------------------------------------

Ground::Ground(const int level, sf::ConvexShape road, std::shared_ptr<b2World> world)
	:m_road(std::move(road))
{
	m_world = world;
	CreateGround();
}

//------------------------------------------

int Ground::getEndPoint() const {
	return static_cast<int>(m_road.getPoint(m_road.getPointCount() - 2).x);
}

//------------------------------------------

void Ground::CreateGround() {
	// The body is also added to the world
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	m_body = m_world->CreateBody(&groundBodyDef);

	// Define the ground box shape
	auto size = m_road.getPointCount();
	b2Vec2* vs = new b2Vec2[size];
	for (auto i = 0; i < size; i++)
		vs[i].Set(m_road.getPoint(i).x, m_road.getPoint(i).y);
	

	b2ChainShape chain;
	chain.CreateLoop(vs, size);

	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &chain;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 1.0f;
	//m_body->CreateFixture(&fixtureDef);
	m_body->CreateFixture(&chain, 1.0f);

	m_body->SetUserData(this);
}
//------------------------------------------

void Ground::draw(sf::RenderWindow& target)  const {

	target.draw(m_road);
}