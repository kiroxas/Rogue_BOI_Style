#include "Door.h"

void Door::collide(const Hittable* e)
{
	if((e->getProperties() & properties::defs::Triggering_global) == properties::defs::Triggering_global
		&& !isLocked())
		Notify(Events::LeaveRoom());
}

Door::Door(const KiroGame::Image& sprite_sheet,CollisionManager* e , float rotation, float scale):
Static_Entity(sprite_sheet,e,rotation,scale)
{
	attack = 0;
}

Door::Door(const KiroGame::Image& sprite_sheet, float rotation, float scale) :
Static_Entity(sprite_sheet,rotation,scale)
{
	attack = 0;
}