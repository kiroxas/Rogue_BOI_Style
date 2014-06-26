#ifndef ROOM_H
#define ROOM_H

#include <array>
#include <vector>
#include "../Misc/Constantes.h"
#include <memory>
#include "../Characters/ICharacter.h"
#include "../Misc/ImagePool.h"
#include <SFML/Graphics.hpp>
#include "../Misc/Suscribable.h"
#include "../Characters/Door.h"

class CollisionManager;
class Maze;

enum RoomType{EMPTY = 0, BOSS};

class Room : public sf::Drawable, 
             Suscribable<Events::LeaveRoom, Events::LeaveRoomArgs>,
             Suscribable<Events::RoomEmpty,void>
{
public :
	using Suscribable<Events::LeaveRoom, Events::LeaveRoomArgs>::Suscribe;
	using Suscribable<Events::LeaveRoom, Events::LeaveRoomArgs>::Notify;
	using  Suscribable<Events::RoomEmpty,void>::Suscribe;
	using  Suscribable<Events::RoomEmpty, void>::Notify;


	explicit Room(RoomType,unsigned int,const ImagePool& p);
	std::vector<Direction> Connectible();
	static bool Connect(Room*, Room*, Direction);
	Room* getNeighboor(Direction);
	void Fill();
	void assignCM(CollisionManager*);
	void desassignCM();
	const std::vector<std::shared_ptr<ICharacter>>& getCharacters() const;
	void update();
	void addCharacter(std::shared_ptr<ICharacter>&);

private :

	friend class Maze;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable
	bool canHasNeighboor();
	void checkConnect();
	void LeftTheRoom(Direction);

	unsigned int number_doors;
	std::array<Room*,4> neighboors;
	bool canConnect;
	RoomType type;
	std::vector<std::shared_ptr<Door>> doors;
	std::vector<std::shared_ptr<ICharacter>> elements;
	std::vector<std::shared_ptr<ICharacter>> heroes;
	const ImagePool& pool;
	std::vector<std::function<void()>> callbacks;
};

Direction opposite(Direction dir);


#endif
