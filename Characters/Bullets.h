#ifndef BULLETS_H
#define BULLETS_H

#include <SFML/Graphics.hpp>
#include <utility>
#include "../Misc/Constantes.h"
#include "Hittable.h"

class CollisionManager;

class Bullets : public sf::Drawable, Hittable
{
	public :

	Bullets(std::pair<int, int> pos, Direction dir,const CollisionManager& e);
	void update();
	Hittable::healthType getDamage() const;
	void collide(Hittable*);
	virtual sf::FloatRect getGlobalBounds() const; 

	private :
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable
    Direction m_dir;
    sf::CircleShape bullet;
};

#endif
