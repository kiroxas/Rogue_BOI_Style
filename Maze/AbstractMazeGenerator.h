#ifndef ABSTRACT_MAZE_GENERATOR
#define ABSTRACT_MAZE_GENERATOR

#include "Maze.h"

class AbstractMazeGenerator
{
public :
	/* Virtual Functions */
	virtual std::unique_ptr<Maze> CreateMaze(unsigned int level_number) = 0;
private :

};

#endif