#include"EndFlag.h"
EndFlag::EndFlag(Resources::TEXTURE texture, std::shared_ptr<b2World> world, sf::Vector2f pos)
	: StaticObject(texture, world, pos)
{
    m_body->GetFixtureList()->SetSensor(true);
}
