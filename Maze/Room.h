#ifndef ROOM_H
#define ROOM_H

#include <array>
#include <vector>
#include "../Misc/Constantes.h"
#include <memory>
#include "../Characters/ICharacter.h"
#include "../Misc/ImagePool.h"
#include <SFML/Graphics.hpp>

class CollisionManager;
class Maze;

enum RoomType{EMPTY = 0, BOSS};

class Room : public sf::Drawable
{
public :
	explicit Room(RoomType,unsigned int,const ImagePool& p);
	std::vector<Direction> Connectible();
	static bool Connect(Room*, Room*, Direction);
	Room* getNeighboor(Direction);
	void Fill();
	void assignCM(CollisionManager*);
	const std::vector<std::shared_ptr<ICharacter>>& getCharacters() const;
	void update();
	void addCharacter(std::shared_ptr<ICharacter>&);
	bool hasLeftRoom() const;
    Direction nextRoomDirection() const;

private :

	friend class Maze;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable
	bool canHasNeighboor();
	void checkConnect();
	void LeftTheRoom(Direction);
	void ResetRoom();

	unsigned int number_doors;
	std::array<Room*,4> neighboors;
	bool canConnect;
	RoomType type;
	std::vector<std::shared_ptr<ICharacter>> elements;
	const ImagePool& pool;
	std::vector<std::function<void()>> callbacks;
	Direction next_room_dir;
	bool has_left = false;
};

Direction opposite(Direction dir);


#endif
