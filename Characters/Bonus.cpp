#include "Bonus.h"
#include "Hittable.h"

Bonus::Bonus(type h, type m_h, type a) :
health(h),
max_health(m_h),
attack(a),
f(BulletEffect::Wavy)
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