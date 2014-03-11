#include "eventDecorator.h"

void eventDecorator::collide(const Hittable* e)
{
	Notify(Events::LeaveRoom(), NORTH);
	component->collide(e); //Chain for other decorators
}
