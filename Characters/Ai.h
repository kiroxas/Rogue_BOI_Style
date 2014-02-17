#ifndef CHARACTER_AI
#define CHARACTER_AI

#include <SFML/System.hpp>
#include "../Misc/Listener.h"

class Ai  : public Listener<Events::Move,Events::MoveArgs>,
			public Listener<Events::Shoot, void>
{
   public :
   using Listener<Events::Shoot,void>::Listen;
   using Listener<Events::Move, std::pair<int,int>>::Listen;

   using Listener<Events::Shoot,void>::Trigger;
   using Listener<Events::Move, std::pair<int,int>>::Trigger;
	void update();
   private :
        sf::Clock m_clock;
	 const sf::Time elapsed_time = sf::seconds(1);
};

#endif
