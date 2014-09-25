#include "Item.h"

void Item::collide(Hittable* e)
{
	if(!consumed && (e->getProperties() & properties::defs::Triggering_global) == properties::defs::Triggering_global)
	{
		effect.applyTo(e);
		consumed = true;
	}
}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    s.setRadius(10);
    s.setPosition(200,200);

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