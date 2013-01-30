#ifndef NORMAL_MAZE_GENERATOR_H
#define NORMAL_MAZE_GENERATOR_H

#include "AbstractMazeGenerator.h"
#include "Maze.h"

class NormalMazeGenerator : public AbstractMazeGenerator
{
	public :
	/* Virtual Functions */
	NormalMazeGenerator(unsigned int);
	virtual std::unique_ptr<Maze> CreateMaze();
private :
	unsigned int level_number;
};

#endif