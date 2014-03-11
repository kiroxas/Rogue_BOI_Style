#ifndef SUSCRIBABLE_H
#define SUSCRIBABLE_H

#include <vector>
#include <functional>
#include <map>
#include "Constantes.h"
#define EVENT(e) struct e{};

namespace Events
{
  EVENT(Move)
  EVENT(Shoot)
  EVENT(Quit)
  EVENT(LeaveRoom)

  using LeaveRoomArgs = Direction;
  using MoveArgs = std::pair<int,int>;
};

template<typename T, typename U>
class Suscribable
{
	using fun = std::function<void(U)>;
	public :

	virtual void Suscribe(T,fun f){callbacks.push_back(f);};

	protected : 
	virtual void Notify(T,U arg){for(auto&e : callbacks) e(arg);};

    std::vector<fun> callbacks;
};

template<typename T>
class Suscribable<T,void>
{
	using fun = std::function<void()>;
	public :

	virtual void Suscribe(T,fun f){callbacks.push_back(f);}

	protected : 
	virtual void Notify(T) const{for(auto&e : callbacks) e();}
	 std::vector<fun> callbacks;
};

#endif
