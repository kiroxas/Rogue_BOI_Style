#ifndef CHARACTER_AI
#define CHARACTER_AI

#include <SFML/System.hpp>
#include "../Misc/Suscribable.h"

class Ai  : public Suscribable<Events::Move, void(Events::MoveArgs)>, // Move
			public Suscribable<Events::Shoot, void(void)> //Shoot
{
   public :
     using Move = Suscribable<Events::Move, void(Events::MoveArgs)>;
     using Shoot = Suscribable<Events::Shoot, void(void)>;
	 void update();

   private :
   sf::Clock m_clock;
	 const sf::Time elapsed_time = sf::seconds(1);
};

#endif
