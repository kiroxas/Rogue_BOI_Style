#ifndef DOOR_H
#define DOOR_H

#include "Static_Entity.h"
#include "../Misc/Lockable.h"
#include "../Misc/Suscribable.h"

class Door : public Static_Entity,
			 public Lockable,
			 public Suscribable<Events::LeaveRoom, void(void)>
{
	public : 
	
	Door(const KiroGame::Image& sprite_sheet,CollisionManager* e, float rotation = 0, float scale = 1);
	Door(const KiroGame::Image& sprite_sheet, float rotation = 0, float scale = 1);
	virtual void collide(const Hittable* e);


};
#endif