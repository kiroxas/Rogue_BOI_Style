#ifndef HITTABLE_H
#define HITTABLE_H

#include <SFML/Graphics.hpp>

struct Hittable : public sf::Transformable 
{
	using healthType = unsigned long long;

	virtual healthType getDamage() const =0;
	virtual void collide(Hittable*) =0;

	protected :
	healthType health;
	healthType attack; 
};



#endif