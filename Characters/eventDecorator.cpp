#include "eventDecorator.h"

void eventDecorator::collide(const Hittable* e)
{
	Trigger(Events::LeaveRoom(), NORTH);
	component->collide(e); //Chain for other decorators
}
