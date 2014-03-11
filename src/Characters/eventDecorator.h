#ifndef EVENT_DECORATOR
#define EVENT_DECORATOR

#include "Hittable.h"
#include "CharacterDecorator.h"
#include "../Misc/Suscribable.h"

class eventDecorator : public CharacterDecorator,
					   public Suscribable<Events::LeaveRoom,Events::LeaveRoomArgs>
{
	public : 
	 using  Suscribable<Events::LeaveRoom,Events::LeaveRoomArgs>::Suscribe;
	 using  Suscribable<Events::LeaveRoom,Events::LeaveRoomArgs>::Notify;

	 eventDecorator(ICharacter* e) : CharacterDecorator(e){}
	 virtual void collide(const Hittable* e);

};

#endif