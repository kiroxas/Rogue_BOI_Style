#include "eventDecorator.h"

void eventDecorator::collide(const Hittable* e)
{
	std::cout << "Event decorator collide : " << static_cast<int>(e->getProperties()) << std::endl;
	if((e->getProperties() & properties::defs::Triggering_global) == properties::defs::Triggering_global)
		Notify(Events::LeaveRoom(), NORTH);
	component->collide(e); //Chain for other decorators
}
