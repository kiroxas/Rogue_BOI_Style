#ifndef DRUNK_MAZE_GENERATOR_H
#define DRUNK_MAZE_GENERATOR_H

#include "AbstractMazeGenerator.h"
#include "Maze.h"

class DrunkMazeGenerator : public AbstractMazeGenerator
{
	public :
	/* Virtual Functions */
	DrunkMazeGenerator(unsigned int);
	virtual std::unique_ptr<Maze> CreateMaze();
private :
	unsigned int level_number;
};

#endif