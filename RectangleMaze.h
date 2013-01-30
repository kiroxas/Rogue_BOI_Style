#ifndef RECTANGLE_MAZE_H
#define RECTANGLE_MAZE_H

#include "Maze.h"

class RectangleMaze : public Maze
{
	public :
	/* Constructeurs */
	explicit RectangleMaze(int);

	/* Destructeur */
	~RectangleMaze();

private :
	virtual void GenerateGraphStructure();
	virtual void FillWithRooms();
};

#endif