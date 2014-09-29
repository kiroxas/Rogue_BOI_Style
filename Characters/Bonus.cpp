#include "Bonus.h"
#include "Hittable.h"

Bonus::Bonus(type h, type m_h, type a) :
health(h),
max_health(m_h),
attack(a),
f([](BulletEffect::arg pos, Direction dir){
			switch(dir)
			{
				case WEST : pos.x += 4; break;
	  			case EAST : pos.x -= 4; break;
	   			case NORTH : pos.y += 4; break;
	   			case SOUTH : pos.y -= 4;
			}
			return pos;
		})
{}

void Bonus::applyTo(Hittable* e) const
{
	e->health += health;
	e->health_max += max_health;
	e->setBulletEffect(f);
}

void Bonus::clear()
{
	health = 0;
	max_health = 0;
	attack = 0;
}