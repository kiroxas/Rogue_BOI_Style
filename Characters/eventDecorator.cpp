#include "eventDecorator.h"

void eventDecorator::collide(Hittable* e)
{
	if((e->getProperties() & properties::defs::Triggering_global) == properties::defs::Triggering_global)
		Notify();

	component->collide(e); //Chain for other decorators
}
