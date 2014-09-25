#include "Hittable.h"

Hittable::Hittable(const CollisionManager* e) : health(1), health_max(1), attack(0), col(e){}

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