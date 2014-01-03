/*  Static_Entity.h
   File that defines an object that is supposed to be static
   author : Mouton Guillaume (Kiroxas)
*/

#ifndef STATIC_ENTITY_H
#define STATIC_ENTITY_H

#include "Character.h"

class Static_Entity : public Character
{
	public :

	Static_Entity(const KiroGame::Image& sprite_sheet,const CollisionManager& e, float rotation = 0, float scale = 1);
	virtual void Move(int x, int y);
};

#endif