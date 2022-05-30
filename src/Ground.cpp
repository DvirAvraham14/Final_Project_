#include "Ground.h"
Ground::Ground(const int level,sf::ConvexShape road,std::shared_ptr<b2World> world)
	:m_road(std::move(road))
{
	//std::cout << m_road << "\n";
	m_world=world;
	auto mapIndex=static_cast<Resources::TEXTURE>(level +6);
	m_sprite.setTexture(Resources::instance().getTexture(mapIndex, true));
	auto s = static_cast<int>(m_road.getPoint(m_road.getPointCount() - 2).x);
	m_sprite.setTextureRect({ 0, 0 , s, HEIGHT_WINDOW });
	CreateGround();
}
int Ground::getEndPoint() const {
	return static_cast<int>(m_road.getPoint(m_road.getPointCount() - 2).x);
}
void Ground::CreateGround() {
	// The body is also added to the world
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	m_body = m_world->CreateBody(&groundBodyDef);

	// Define the ground box shape
	auto size = m_road.getPointCount();
	std::cout << size;
	b2Vec2* vs = new b2Vec2[size];
	for (auto i = 0; i < size; i++)
		vs[i].Set(m_road.getPoint(i).x, m_road.getPoint(i).y);
	b2ChainShape chain;
	chain.CreateLoop(vs, size);
	m_body->CreateFixture(&chain, 1.0f);
	m_body->SetUserData(this);
}
void Ground::draw(sf::RenderWindow& target)  const {
	target.draw(m_sprite);
	target.draw(m_road);
}