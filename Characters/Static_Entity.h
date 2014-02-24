/*  Static_Entity.h
   File that defines an object that is supposed to be static
   author : Mouton Guillaume (Kiroxas)
*/

#ifndef STATIC_ENTITY_H
#define STATIC_ENTITY_H

#include <SFML/Graphics.hpp>
#include "Character.h"

class Static_Entity : public Character
{
	public :

	Static_Entity(const KiroGame::Image& sprite_sheet,CollisionManager* e, float rotation = 0, float scale = 1);
	Static_Entity(const KiroGame::Image& sprite_sheet, float rotation = 0, float scale = 1);
	virtual void Move(std::pair<int, int>);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif

