#ifndef ITEM_H
#define ITEM_H

#include "Hittable.h"
#include "CharacterAnimation.h"
#include "Bonus.h"
#include <memory>

enum Category
{
	VideoGame,
	SF,
	Fantasy,
	Reality,
	None
};

class Item : public Hittable, public sf::Drawable
{
public :
	Item() :effect(Bonus(0,1,0)){}
	void collide(Hittable*);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::FloatRect getGlobalBounds() const;
	bool isConsumed() const;

private:
	mutable sf::CircleShape s;
	Bonus effect;
	CharacterAnimation display;
	Category gt;
	bool consumed = false;
};

#endif