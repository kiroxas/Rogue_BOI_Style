#include "DrunkMazeGenerator.h"
#include "../Misc/Constantes.h"
#include <memory>

DrunkMazeGenerator::DrunkMazeGenerator(const ImagePool& p,CollisionManager& _c) :
	pool(p),
	c(_c)
{}

std::unique_ptr<Maze> DrunkMazeGenerator::CreateMaze(unsigned int l)
{
	infos::log(MAZE_LOG_PATH,"Generating Maze from NormalMaze");

	std::unique_ptr<Maze> g(new Maze(NUMBER_OF_ROOMS + 2*l,pool,c));
	g->GenerateDrunkStructure();

	return g;
}
