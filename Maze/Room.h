#ifndef ROOM_H
#define ROOM_H

#include <array>
#include <vector>
#include "../Misc/Constantes.h"
#include <memory>
#include "../Characters/Character.h"
#include "../Misc/ImagePool.h"
#include <SFML/Graphics.hpp>

enum RoomType{EMPTY = 0, BOSS};

class Room : public sf::Drawable
{
public :
	explicit Room(RoomType,unsigned int,const ImagePool& p);
	std::vector<Direction> Connectible();
	static bool Connect(Room*, Room*, Direction);
	Room* getNeighboor(Direction);
	void Fill();

private :
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable
	bool canHasNeighboor();
	void checkConnect();

	unsigned int number_doors;
	std::array<Room*,4> neighboors;
	bool canConnect;
	RoomType type;
	std::vector<std::unique_ptr<Character>> elements;
	const ImagePool& pool;
};

Direction opposite(Direction dir);


#endif