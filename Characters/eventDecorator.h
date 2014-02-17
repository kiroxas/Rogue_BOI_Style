#ifndef EVENT_DECORATOR
#define EVENT_DECORATOR

#include "Hittable.h"
#include "CharacterDecorator.h"

class eventDecorator : public CharacterDecorator
{
	 virtual void collide(const Hittable*);
};

#endif