#include "Bullets.h"
#include "CollisionManager.h"
#include <iostream>

Bullets::Bullets(std::pair<int,int> pos, Direction dir, Func f, const CollisionManager* e) :
Hittable(e),
m_dir(dir)
{
	attack = 1;
	health = 1;
	bullet.setPosition(pos.first,pos.second);
	bullet.setRadius(7);
	bullet.setFillColor(sf::Color::Blue);
	bullet.setOutlineColor(sf::Color::Red);
	if(col)
	{
	   col->registerEntity(this);
	   registered = true;
	}
	state = properties::defs::Nothing;
	move_func = setFunction(f);
}

Bullets::moveFunction Bullets::setFunction(Func f)
{
	return [this,f](){return f(bullet.getPosition(),this->m_dir);};
}

Bullets::~Bullets()
{
   if(registered && col)
	 col->unregisterEntity(this);
}

void Bullets::update()
{
	if(!isDead())
	{
		auto pos = bullet.getPosition();
		auto old_pos = pos;

		pos = move_func();
		bullet.setPosition(pos);

		if(col && !col->canIMove(this))
		{
			setPosition(old_pos);
		}	
	}	
}


sf::FloatRect Bullets::getGlobalBounds() const
{
	return bullet.getGlobalBounds();
}


void Bullets::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//states.transform = getTransform();
	target.draw(bullet,states);
}

Hittable::healthType Bullets::getDamage() const
{
	return attack;
}

void Bullets::collide(Hittable*)
{
	health = 0;
}

bool Bullets::isDead() const
{
	return health == 0;
}

void Bullets::die()
{
	health = 0;
}

