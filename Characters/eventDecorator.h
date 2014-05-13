#ifndef EVENT_DECORATOR
#define EVENT_DECORATOR

#include "Hittable.h"
#include "CharacterDecorator.h"
#include "../Misc/Suscribable.h"

class eventDecorator : public CharacterDecorator,
					   public Suscribable<Events::LeaveRoom,void>
{
	public : 
	 using  Suscribable<Events::LeaveRoom,void>::Suscribe;
	 using  Suscribable<Events::LeaveRoom, void>::Notify;

	 eventDecorator(ICharacter* e) : CharacterDecorator(e){}
	 virtual void collide(const Hittable* e);

};

#endif