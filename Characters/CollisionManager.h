#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include <vector>
#include "../Misc/GameInfo.h"

struct Hittable;

class CollisionManager
{
	public : 
	CollisionManager(GameInfo&);
	void registerEntity(Hittable*) const;
	void unregisterEntity(Hittable* ent) const;
	bool canIMove(Hittable*) const;

	private :

	mutable std::vector<Hittable*> entities;
	GameInfo& stats;
};
#endif
