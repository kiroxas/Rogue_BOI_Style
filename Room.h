#ifndef ROOM_H
#define ROOM_H

#include <array>
#include <vector>

enum RoomType{EMPTY = 0, BOSS};
enum Direction{NORTH = 0,  EAST,SOUTH,WEST};

class Room
{
public :
	explicit Room(RoomType,unsigned int);
	std::vector<Direction> Connectible();
	static bool Connect(Room*, Room*, Direction);
	Room* getNeighboor(Direction);

private :
	bool canHasNeighboor();
	void checkConnect();

	unsigned int number_doors;
	std::array<Room*,4> neighboors;
	bool canConnect;
	RoomType type;
};

Direction opposite(Direction dir);


#endif