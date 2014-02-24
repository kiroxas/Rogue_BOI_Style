#ifndef NORMAL_MAZE_GENERATOR_H
#define NORMAL_MAZE_GENERATOR_H

#include "AbstractMazeGenerator.h"
#include "Maze.h"
#include "../Characters/CollisionManager.h"

class NormalMazeGenerator : public AbstractMazeGenerator
{
	public :
	/* Virtual Functions */
	NormalMazeGenerator(const ImagePool& p);
	virtual std::unique_ptr<Maze> CreateMaze(unsigned int);
private :
	const ImagePool& pool;
};

#endif
