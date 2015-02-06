#include "CollisionManager.h"
#include "Hittable.h"
#include <iostream>
#include "../Misc/Constantes.h"

CollisionManager::CollisionManager(GameInfo& s)
: stats(s){}

Registration CollisionManager::registerEntity(Hittable* ent) 
{
	/*if(ent)
		entities.push_back(ent);*/
	UniversalPointer f = UniversalPointer((void*)ent,[](void* e){std::cout << "Deleted " << e <<std::endl;});
	return SubjectBase::registerObserver(std::move(f));
}

/*void CollisionManager::unregisterEntity(Hittable* ent) const
{
	auto it = std::find(entities.begin(),entities.end(),ent);
	if(it != entities.end())
		entities.erase(it);
}
*/
bool CollisionManager::canIMove(Hittable* me) const
{
	if(me == nullptr || !KiroGame::isInInnerRoom(me->getGlobalBounds()))
	{
		return false;
	}
	bool res = true;

	for(const auto& fp : observers)
	{
		Hittable* e = (Hittable*)fp.get();
		if(!e || e == me || e->isDead() || e->sameTeam(me)) 
			continue;
		
		if(me->getGlobalBounds().intersects(e->getGlobalBounds()))
		{
			e->collide(me);
			me->collide(e);
			if(e->isDead())
				stats.KilledAnEnnemy();
			std::cout << "splash" << std::endl;
			res = false;
			if(me->isDead())
				return res;
		}
	}
	
	return res;
}
