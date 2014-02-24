#include "DrunkMazeGenerator.h"
#include "../Misc/Constantes.h"
#include <memory>

DrunkMazeGenerator::DrunkMazeGenerator(const ImagePool& p) :
	pool(p)
{}

std::unique_ptr<Maze> DrunkMazeGenerator::CreateMaze(unsigned int l)
{
	infos::log(MAZE_LOG_PATH,"Generating Maze from NormalMaze");

	std::unique_ptr<Maze> g(new Maze(NUMBER_OF_ROOMS + 2*l,pool));
	g->GenerateDrunkStructure();

	return g;
}
