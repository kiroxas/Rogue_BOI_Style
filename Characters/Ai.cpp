#include "Ai.h"
#include <random>

void Ai::update()
{
   if(m_clock.getElapsedTime() >= elapsed_time)
    {
		static std::random_device rd;
    	static std::mt19937 generator(rd());
    	static std::bernoulli_distribution dist(0.5);
    	static std::uniform_int_distribution<int> dist2(-1,1);
		if(dist(generator))
			Move::Notify(std::make_pair(10 * dist2(generator),10 * dist2(generator)));
		else
			Shoot::Notify();
		m_clock.restart();
    }
}
