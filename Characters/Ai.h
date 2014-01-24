#ifndef CHARACTER_AI
#define CHARACTER_AI

#include <SFML/System.hpp>
#include "../Misc/Listener.h"

class Ai : public Listener
{
   public :
	void update();
   private :
        sf::Clock m_clock;
	 const sf::Time elapsed_time = sf::seconds(1);
};

#endif
