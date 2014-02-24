#ifndef CHARACTER_AI
#define CHARACTER_AI

#include <SFML/System.hpp>
#include "../Misc/Suscribable.h"

class Ai  : public Suscribable<Events::Move,Events::MoveArgs>,
			      public Suscribable<Events::Shoot, void>
{
   public :
   using Suscribable<Events::Shoot,void>::Suscribe;
   using Suscribable<Events::Move, std::pair<int,int>>::Suscribe;

   using Suscribable<Events::Shoot,void>::Notify;
   using Suscribable<Events::Move, std::pair<int,int>>::Notify;
	 void update();

   private :
   sf::Clock m_clock;
	 const sf::Time elapsed_time = sf::seconds(1);
};

#endif
