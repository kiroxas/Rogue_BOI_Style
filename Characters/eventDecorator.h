#ifndef EVENT_DECORATOR
#define EVENT_DECORATOR

#include "Hittable.h"
#include "CharacterDecorator.h"
#include "../Misc/Listener.h"

class eventDecorator : public CharacterDecorator,
					   public Listener<Events::LeaveRoom,Events::LeaveRoomArgs>
{
	public : 
	 using  Listener<Events::LeaveRoom,Events::LeaveRoomArgs>::Listen;
	 using  Listener<Events::LeaveRoom,Events::LeaveRoomArgs>::Trigger;

	 eventDecorator(ICharacter* e) : CharacterDecorator(e){}
	 virtual void collide(const Hittable* e);

};

#endif