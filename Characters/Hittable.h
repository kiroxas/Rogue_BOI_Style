#ifndef HITTABLE_H
#define HITTABLE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "CharacterAnimation.h"
#include "CollisionManager.h"

struct Hittable : public sf::Transformable 
{
	Hittable(const CollisionManager* e = nullptr) : col(e){}
	using healthType = unsigned long long;

	virtual void assignCM(CollisionManager* e){col = e; col->registerEntity(this);}
	virtual void desassignCM(){col->unregisterEntity(this);}
	virtual healthType getDamage() const {return attack;};
	virtual void collide(const Hittable*) =0;
	virtual sf::FloatRect getGlobalBounds() const =0; 
	virtual ~Hittable(){}
	virtual bool isDead() const {return health == 0;}

	protected :

    virtual void setDamage(healthType e){attack = e;}
	healthType health;
	healthType attack; 
	const CollisionManager* col;
	bool registered;
};



#endif
