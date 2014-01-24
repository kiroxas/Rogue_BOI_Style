#include "Listener.h"

void Listener::ListenToShoot(std::function<void()> f)
{
	shootFuncs.emplace_back(f);
}

void Listener::ListenToQuit(std::function<void()> f)
{
	quitFuncs.emplace_back(f);
}

void Listener::ListenToMove(std::function<void(int,int)> a)
{
	moveFuncs.push_back(a);
}

void Listener::triggerMove(int x, int y)
{
	for(auto e : moveFuncs)
	{
		e(x,y);
	}
}

void Listener::triggerQuit()
{
	for(auto&e : quitFuncs)
		e();
}

void Listener::triggerShoot()
{
	for(auto&e : shootFuncs)
		e();
}
