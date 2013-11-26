#ifndef BULLETS_H
#define BULLETS_H

#include <SFML/Graphics.hpp>
#include <utility>
#include "../Misc/Constantes.h"

class Bullets : public sf::Drawable
{
	public :

	Bullets(std::pair<int, int> pos, Direction dir);
	void update();
	sf::FloatRect getGlobalBounds()	const;
	bool fake() const;

	private :
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable
    Direction m_dir;
    sf::CircleShape bullet;
};

#endif