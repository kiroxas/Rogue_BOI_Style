#include "Item.h"

void Item::collide(Hittable* e)
{
	if(!consumed && (e->getProperties() & properties::defs::Triggering_global) == properties::defs::Triggering_global)
	{
		effect.applyTo(e);
		consumed = true;
		//desassignCM();
		//std::cout << "desassigned : " << this << std::endl;
	}
}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(s,states);
}

sf::FloatRect Item::getGlobalBounds() const
{
	return s.getGlobalBounds();
}

bool Item::isConsumed() const
{
	return consumed;
}

Item::Item(int x, int y)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int> distribution(0,10);
	effect = Bonus(1,0,0);
	s.setRadius(10);
	s.setPosition(x,y);
}
