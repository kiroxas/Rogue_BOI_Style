#ifndef LISTENER_H
#define LISTENER_H

#include <vector>
#include <functional>

class Listener
{
	public :

	virtual void ListenToMove(std::function<void(int,int)>);
	virtual void ListenToShoot(std::function<void()>);
	virtual void ListenToQuit(std::function<void()>);

	protected : 

	void triggerMove(int x, int y);
	void triggerShoot();
	void triggerQuit();

	std::vector<std::function<void(int,int)>> moveFuncs;
	std::vector<std::function<void()>> shootFuncs;
	std::vector<std::function<void()>> quitFuncs;
};

#endif
