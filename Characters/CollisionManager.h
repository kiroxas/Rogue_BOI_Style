#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include <vector>
#include "Hittable.h"

class CollisionManager
{
	public : 

	void registerEntity(Hittable*) const;
	bool canIMove(const Hittable*) const;

	private :

	mutable std::vector<Hittable*> entities;
};
#endif