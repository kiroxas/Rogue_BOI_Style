#include "CollisionManager.h"

void CollisionManager::registerEntity(Hittable* ent) const
{
	entities.emplace_back(ent);
}