#include "CollisionManager.h"
#include "Hittable.h"
#include <iostream>
#include "../Misc/Constantes.h"

CollisionManager::CollisionManager(GameInfo& s)
: stats(s){}

void CollisionManager::registerEntity(Hittable* ent) const
{
	if(ent)
		entities.push_back(ent);
}

void CollisionManager::unregisterEntity(Hittable* ent) const
{
	auto it = std::find(entities.begin(),entities.end(),ent);
	if(it != entities.end())
		entities.erase(it);
}

bool CollisionManager::canIMove(Hittable* me) const
{
	if(me == nullptr || !KiroGame::isInInnerRoom(me->getGlobalBounds()))
		return false;
	bool res = true;

	for(auto e : entities)
	{
		if(e == me || e->isDead() || e->sameTeam(me)) 
			continue;
		
		if(me->getGlobalBounds().intersects(e->getGlobalBounds()))
		{
			e->collide(me);
			me->collide(e);
			if(e->isDead())
				stats.KilledAnEnnemy();
			res = false;
		}
	}
	
	return res;
}
