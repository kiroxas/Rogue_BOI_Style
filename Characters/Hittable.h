#ifndef HITTABLE_H
#define HITTABLE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "CharacterAnimation.h"
#include "CollisionManager.h"
#include <iostream>

namespace properties
{
   enum class defs : int
   {
      Triggering_global = 1,
      Triggering_local = 2,
      Invincible = 4,
      Nothing = 8
   };

   inline defs operator&(const defs& f, const defs& other)
   {
   		return static_cast<defs>(static_cast<int>(f) & static_cast<int>(other));
   }

   inline defs operator|(const defs& f, const defs& other)
   {
   		return static_cast<defs>(static_cast<int>(f) | static_cast<int>(other));
   }
};


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
	virtual bool isDead() const {return health <= 0;}
	virtual properties::defs getProperties() const {return state;}
	virtual void setProperties(const properties::defs d){state = d;}

	protected :

    virtual void setDamage(healthType e){attack = e;}
	healthType health;
	healthType attack; 
	const CollisionManager* col;
	bool registered;
	properties::defs state;
};



#endif
