#include "CollisionManager.h"

void CollisionManager::registerEntity(Hittable* ent) const
{
	entities.emplace_back(ent);
}

bool CollisionManager::canIMove(const Hittable* me) const
{
	for(auto e : entities)
	{
		if(e == me)
			continue;
		
		//if(e-> getPosition())
		//{}
	}
	
	return true;
}