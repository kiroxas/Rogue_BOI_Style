#ifndef MAZE_H
#define MAZE_H

#pragma warning(push, 0)
#include <memory>
#include <vector>
#include <set>
#pragma warning(pop)

#include "Room.h"
#include "RoomFactory.h"
#include "../Misc/ImagePool.h"

#define MAX_IND 10000

class Maze 
{
	typedef std::vector<std::unique_ptr<Room>> myMaze;

public :
	/* Constructeurs */
	explicit Maze(unsigned int, const ImagePool&);

	/* Destructeur */
	virtual ~Maze();

	virtual void GenerateGraphStructure();
	virtual void GenerateDrunkStructure();
	Room* getSeedRoom() const;
	unsigned int getNumberRooms() const;
	Room* getCurrentRoom() const;

private :

	unsigned int m_numberOfRooms;
	myMaze m_maze;
	unsigned int my_room;
	RoomFactory god_room;
	const ImagePool& pool;
};

std::set<unsigned int> find_biggest_connection(const std::vector<std::pair<unsigned int,unsigned int>>&);
std::array<unsigned int, 4> find_neighboors(const std::vector<std::pair<int, int>>&, const std::pair<int,int>&);
	 
#endif