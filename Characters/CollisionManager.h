#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include <vector>

class Hittable;

class CollisionManager
{
	public : 

	void registerEntity(Hittable*) const;

	private :

	mutable std::vector<Hittable*> entities;
};
#endif