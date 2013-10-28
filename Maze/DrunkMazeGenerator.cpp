#include "DrunkMazeGenerator.h"
#include "../Misc/Constantes.h"
#include <memory>

DrunkMazeGenerator::DrunkMazeGenerator(unsigned int number) :
	level_number(number)
{}

std::unique_ptr<Maze> DrunkMazeGenerator::CreateMaze()
{
	infos::log(MAZE_LOG_PATH,"Generating Maze from NormalMaze");

	std::unique_ptr<Maze> g(new Maze(NUMBER_OF_ROOMS + 2*level_number));
	g->GenerateDrunkStructure();

	return g;
}
