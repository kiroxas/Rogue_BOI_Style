#include "Ai.h"
#include <random>

void Ai::update()
{
   if(m_clock.getElapsedTime() >= elapsed_time)
    {
	static std::random_device rd;
    	static std::mt19937 generator(rd());
    	static std::bernoulli_distribution dist(0.5);
	if(dist(generator))
		triggerShoot();
	else
		triggerMove(10 * dist(generator),10 * dist(generator));
	m_clock.restart();
    }
}
