#include "Bullets.h"

Bullets::Bullets(std::pair<int,int> pos, Direction dir) :
m_dir(dir)
{
	bullet.setPosition(pos.first,pos.second);
	bullet.setRadius(7);
	bullet.setFillColor(sf::Color::Blue);
	bullet.setOutlineColor(sf::Color::Red);
}

void Bullets::update()
{
	auto pos = bullet.getPosition();

	switch(m_dir)
	{
		case NORTH : pos.y -= 4; break;
		case SOUTH : pos.y += 4; break;
		case EAST : pos.x += 4; break;
		case WEST : pos.x -= 4; break;
	}

	bullet.setPosition(pos);
}


sf::FloatRect Bullets::getGlobalBounds() const
{
	return bullet.getGlobalBounds();
}

bool Bullets::fake() const
{
	return false;
}

void Bullets::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//states.transform = getTransform();
	target.draw(bullet,states);
}