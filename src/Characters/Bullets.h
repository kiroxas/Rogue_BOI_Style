#ifndef BULLETS_H
#define BULLETS_H

#include <SFML/Graphics.hpp>
#include <utility>
#include "../Misc/Constantes.h"
#include "Hittable.h"

class CollisionManager;

class Bullets : public Hittable, public sf::Drawable
{
	public :

	Bullets(std::pair<int, int> pos, Direction dir,const CollisionManager* e = nullptr);
	~Bullets();
	void update();
	Hittable::healthType getDamage() const;
	void collide(const Hittable*);
	virtual sf::FloatRect getGlobalBounds() const; 
	bool isDead() const;
	void die();

	private :
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable
    Direction m_dir;
    sf::CircleShape bullet;
};

#endif
