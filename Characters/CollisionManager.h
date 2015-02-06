#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include <vector>
#include "../Misc/GameInfo.h"
#include "../Misc/Suscribable.h"

struct Hittable;

class CollisionManager : public SubjectBase
{
	public : 
	CollisionManager(GameInfo&);
	Registration registerEntity(Hittable*);
	//void unregisterEntity(Hittable* ent) const;
	bool canIMove(Hittable*) const;

	private :

	//mutable std::vector<Hittable*> entities;
	GameInfo& stats;
};
#endif
