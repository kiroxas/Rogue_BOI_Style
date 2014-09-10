#include "eventDecorator.h"

void eventDecorator::collide(const Hittable* e)
{
	if((e->getProperties() & properties::defs::Triggering_global) == properties::defs::Triggering_global)
		Notify();

	component->collide(e); //Chain for other decorators
}
