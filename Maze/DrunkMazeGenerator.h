#ifndef DRUNK_MAZE_GENERATOR_H
#define DRUNK_MAZE_GENERATOR_H

#include "AbstractMazeGenerator.h"
#include "Maze.h"
#include "../Characters/CollisionManager.h"

class DrunkMazeGenerator : public AbstractMazeGenerator
{
	public :
	/* Virtual Functions */
	DrunkMazeGenerator(const ImagePool& p);
	virtual std::unique_ptr<Maze> CreateMaze(unsigned int level_number);
private :
	const ImagePool& pool;
};

#endif
