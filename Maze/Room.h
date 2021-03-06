#ifndef ROOM_H
#define ROOM_H

#include <array>
#include <vector>
#include "../Misc/Constantes.h"
#include <memory>
#include "../Characters/ICharacter.h"
#include "../Characters/Ai.h"
#include "../Misc/ImagePool.h"
#include <SFML/Graphics.hpp>
#include "../Misc/Suscribable.h"
#include "../Characters/Door.h"
#include "../Characters/Item.h"

class CollisionManager;
class Maze;

enum RoomType{EMPTY = 0, BOSS, TREASURE};

class Room : public sf::Drawable, 
             public Suscribable<Events::LeaveRoom, void(Events::LeaveRoomArgs)>,
             public Suscribable<Events::RoomEmpty,void(void)>
{
public :

	using Suscribable<Events::LeaveRoom, void(Events::LeaveRoomArgs)>::Notify;
	using Suscribable<Events::LeaveRoom, void(Events::LeaveRoomArgs)>::Suscribe;
	using Suscribable<Events::RoomEmpty, void(void)>::Notify;
	using Suscribable<Events::RoomEmpty, void(void)>::Suscribe;
	using RoomEmpty = Suscribable<Events::RoomEmpty, void(void)>;
	using LeaveRoom = Suscribable<Events::LeaveRoom, void(Events::LeaveRoomArgs)>;
	using Itemcollection = std::vector<Item>;

	explicit Room(RoomType,unsigned int,const ImagePool& p);
	std::vector<Direction> Connectible();
	static bool Connect(Room*, Room*, Direction);
	Room* getNeighboor(Direction);
	void Fill();
	void assignCM(CollisionManager*);
	void desassignCM();
	std::vector<std::unique_ptr<ICharacter>> getCharacters();
	const std::vector<std::unique_ptr<ICharacter>>& peekAtCharacters() const;
	void update();
	void addCharacter(std::unique_ptr<ICharacter>);
	unsigned long long getNumberOfEnnemies() const;
	bool hasBeenVisited() const;
	void setVisited();
	RoomType getRoomType() const;

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
	std::vector<std::shared_ptr<Character>> elements;
	std::vector<std::unique_ptr<ICharacter>> heroes;
	const ImagePool& pool;
	std::vector<std::function<void()>> callbacks;
	std::vector<Registration> my_reg;
	Ai common_brain;
	std::vector<Registration> ai_reg;
	Itemcollection items;

protected :
	bool visited = false;
};

Direction opposite(Direction dir);


#endif
