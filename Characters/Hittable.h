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

namespace BulletEffect
{
	using arg = sf::Vector2f;
	using Func = std::function<arg(arg,Direction)>;
};

struct Hittable : public sf::Transformable 
{
	Hittable(const CollisionManager* e = nullptr, unsigned int team_number = 0);
	using healthType = unsigned long long;

	virtual void assignCM(CollisionManager* e);
	virtual void desassignCM();
	virtual healthType getDamage() const;
	virtual healthType getHealth() const;
	virtual healthType getMaxHealth() const;
	virtual void collide(Hittable*) =0;
	virtual sf::FloatRect getGlobalBounds() const =0; 
	virtual ~Hittable();
	virtual bool isDead() const;
	virtual properties::defs getProperties() const;
	virtual void setProperties(const properties::defs d);
	virtual void setBulletEffect(BulletEffect::Func);
	virtual bool sameTeam(const Hittable*) const;
	virtual void setTeam(unsigned int t);

	protected :

	friend class Bonus;

    virtual void setDamage(healthType e);

	healthType health;
	healthType health_max;
	healthType attack; 
	const CollisionManager* col;
	unsigned int team_number;

	bool registered;
	properties::defs state;
	BulletEffect::Func bullet_ef;
};



#endif
