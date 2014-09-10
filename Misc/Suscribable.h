#ifndef LISTENER_H
#define LISTENER_H

#include <vector>
#include <functional>
#include <map>
#include <memory>
#include "Constantes.h"
#define EVENT(e) struct e{};

namespace Events
{
  EVENT(Move)
  EVENT(Shoot)
  EVENT(Quit)
  EVENT(LeaveRoom)
  EVENT(RoomEmpty)
  EVENT(HeroAreDead)
  using LeaveRoomArgs = Direction;
  using MoveArgs = std::pair<int,int>;
};

using Registration = std::shared_ptr<void>;

using UniversalPointer = std::shared_ptr<void>;

template<typename Deleter>
UniversalPointer CreateEmptyPtr(Deleter d)
{
	return UniversalPointer((void*)0xDEADC0DE,d);
}

UniversalPointer createHeartBeat();

class SubjectBase
{
	protected :
	SubjectBase();

	Registration registerObserver(UniversalPointer ptr);

	std::vector<UniversalPointer> observers;

	private :

	UniversalPointer heartBeat_;

};

template <typename Event, typename Signature>
struct Suscribable;

template<typename Event, typename Return, typename... params>
struct Suscribable<Event, Return (params...)> : SubjectBase
{
	using F = std::function<Return (params...)>;
	using Fptr = std::shared_ptr<F>;

	void Notify(params... p)
	{
		for(const auto& obs : observers)
		{
			const Fptr fp = std::static_pointer_cast<F>(obs);
			(*fp)(p...);
		}
	}

	Registration Suscribe(F f)
	{
		Fptr fp(new F(std::move(f)));
		return SubjectBase::registerObserver(fp);
	}
};

#endif
