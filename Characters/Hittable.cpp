#include "Hittable.h"

Hittable::Hittable(const CollisionManager* e) : col(e){}

void Hittable::assignCM(CollisionManager* e){col = e; col->registerEntity(this);}

void Hittable::desassignCM(){col->unregisterEntity(this);}

Hittable::healthType Hittable::getDamage() const {return attack;}

Hittable::healthType Hittable::getHealth() const {return health;}

Hittable::healthType Hittable::getMaxHealth() const {return health_max;}

Hittable::~Hittable(){}

bool Hittable::isDead() const {return health <= 0;}

properties::defs Hittable::getProperties() const {return state;}

void Hittable::setProperties(const properties::defs d){state = d;}

void Hittable::setDamage(healthType e){attack = e;}

void Hittable::setBulletEffect(BulletEffect::Func f) {bullet_ef = f;}

bool Hittable::sameTeam(const Hittable* e) const {return team_number == e->team_number;}

void Hittable::setTeam(unsigned int t) {team_number = t;}

void Hittable::setBulletColor(const sf::Color& s) {bullet_color = s;}

void Hittable::addHealth() {health++; if(health > health_max) health = health_max; }

BulletEffect::arg BulletEffect::Straight(arg pos,Direction dir, speedType speed)
{
	switch(dir)
	{
		case WEST : pos.x -= speed; break;
	  	case EAST : pos.x += speed; break;
	   	case NORTH : pos.y -= speed; break;
	   	case SOUTH : pos.y += speed;
	}
	return pos;
}

BulletEffect::arg BulletEffect::Reverse(arg pos,Direction dir, speedType speed)
{
	switch(dir)
	{
		case WEST : pos.x += speed; break;
	  	case EAST : pos.x -= speed; break;
	   	case NORTH : pos.y += speed; break;
	   	case SOUTH : pos.y -= speed;
	}
	return pos;
}

BulletEffect::arg BulletEffect::Wavy(arg pos,Direction dir, speedType speed)
{
	switch(dir)
	{
		case WEST : pos.x -= speed; pos.y += speed * 10 * std::cos(pos.x); break;
	  	case EAST : pos.x += speed; pos.y += speed * 10 * std::cos(pos.x);break;
	   	case NORTH : pos.y -= speed; pos.x += speed * 10 * std::cos(pos.y);break;
	   	case SOUTH : pos.y += speed; pos.x += speed * 10 * std::cos(pos.y);
	}
	return pos;
}
