#include "DrunkMazeGenerator.h"
#include "../Misc/Constantes.h"
#include <memory>

DrunkMazeGenerator::DrunkMazeGenerator(unsigned int number,const ImagePool& p) :
	level_number(number),
	pool(p)
{}

std::unique_ptr<Maze> DrunkMazeGenerator::CreateMaze()
{
	infos::log(MAZE_LOG_PATH,"Generating Maze from NormalMaze");

	std::unique_ptr<Maze> g(new Maze(NUMBER_OF_ROOMS + 2*level_number,pool));
	g->GenerateDrunkStructure();

	return g;
}
