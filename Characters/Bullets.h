#ifndef BULLETS_H
#define BULLETS_H

#include <SFML/Graphics.hpp>
#include <utility>
#include <functional>
#include "../Misc/Constantes.h"
#include "Hittable.h"

class CollisionManager;

class Bullets : public Hittable, public sf::Drawable
{
	public :
	using moveFunction = std::function<BulletEffect::arg()> ;

	Bullets(std::pair<int, int> pos, Direction dir, BulletEffect::Func f, const CollisionManager* e = nullptr);
	~Bullets();
	void update();
	Hittable::healthType getDamage() const;
	void collide(Hittable*);
	virtual sf::FloatRect getGlobalBounds() const; 
	bool isDead() const;
	void die();
	moveFunction setFunction(BulletEffect::Func f);
	void setBulletColor(const sf::Color&);

	private :
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable
    Direction m_dir;
    moveFunction  move_func;
    sf::CircleShape bullet;
};

#endif
