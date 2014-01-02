#ifndef HITTABLE_H
#define HITTABLE_H

#include <SFML/Graphics.hpp>

class CollisionManager;

struct Hittable : public sf::Transformable 
{
	Hittable(const CollisionManager& e) : col(e){}
	using healthType = unsigned long long;

	virtual healthType getDamage() const =0;
	virtual void collide(Hittable*) =0;

	protected :
	healthType health;
	healthType attack; 
	const CollisionManager& col;
};



#endif