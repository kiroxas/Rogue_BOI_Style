/* Room.cpp
   Implementation file of a room
   Author : Guillaume Mouton (Kiroxas)
*/

#include "Room.h"
#include "../Misc/Constantes.h"
#include <vector>
#include <algorithm>

Room::Room(RoomType r,unsigned int n) : 
	type(r),
	number_doors(n),
	canConnect(true)
{
	auto func = [] () {return nullptr; };
	std::generate(neighboors.begin(),neighboors.end(),func);
}

Room* Room::getNeighboor(Direction dir)
{
	return neighboors[dir];
}

std::vector<Direction> Room::Connectible()
{
	std::vector<Direction> res;

	for(unsigned int i = 0; i < 4; ++i)
	{
		if(neighboors[i] == nullptr) res.push_back(static_cast<Direction>(i));
	}

	return res;
}

bool Room::canHasNeighboor()
{
	return canConnect;
}

void Room::checkConnect()
{
	unsigned int cpt = 0;

	for(const auto& x : neighboors)
	{
		if(x != nullptr) ++cpt;
	}

	if(cpt == number_doors) canConnect = false;
}

bool Room::Connect(Room* r1, Room* r2, Direction dir)
{
	if (r1 == nullptr || r2 == nullptr) return false;
	if (r1->neighboors[dir] != nullptr || r2->neighboors[opposite(dir)] != nullptr) return false;
	if (!r1->canHasNeighboor() || !r2->canHasNeighboor()) return false;

	r1->neighboors[dir] = r2;
	r2->neighboors[opposite(dir)] = r1;

	r1->checkConnect();
	r2->checkConnect();

	return true;
}

Direction opposite(Direction dir)
{
	switch(dir)
	{
	case NORTH : return SOUTH;
	case EAST : return WEST;
	case WEST : return EAST;
	case SOUTH : return NORTH;
	default : 
		infos::log(MAZE_LOG_PATH,"Unknown Direction in opposite, exiting");
		exit(1);
	}
}
