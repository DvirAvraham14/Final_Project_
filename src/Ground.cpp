#include "Ground.h"

//___________________________________________________

Ground::Ground(sf::ConvexShape road, std::shared_ptr<b2World> world)
	:m_road(std::move(road))
{
	m_world = world;
	CreateGround();
}

//___________________________________________________

int Ground::getEndPoint() const {
	return static_cast<int>(m_road.getPoint(m_road.getPointCount() - CONST_POINT).x);
}

//___________________________________________________

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
	m_body->CreateFixture(&chain, FIXTURE);
	m_body->SetUserData(this);
}

//___________________________________________________

void Ground::draw(sf::RenderWindow& target)  const {

	target.draw(m_road);
}