#include "CollisionManager.h"
#include "Hittable.h"
#include <iostream>

void CollisionManager::registerEntity(Hittable* ent) const
{
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
	if(me == nullptr)
		return false;
	bool res = true;

	for(auto e : entities)
	{
		if(e == nullptr || e == me) 
			continue;
		
		if(me->getGlobalBounds().intersects(e->getGlobalBounds()))
		{
			(e)->collide(me);
			me->collide(e);
			res = false;
		}
	}
	
	return res;
}
