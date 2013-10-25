#include "NormalMazeGenerator.h"
#include "../Misc/Constantes.h"


NormalMazeGenerator::NormalMazeGenerator()
{}

std::unique_ptr<Maze> NormalMazeGenerator::CreateMaze(unsigned int level_number)
{

	infos::log(MAZE_LOG_PATH,"Generating Maze from NormalMaze");

	std::unique_ptr<Maze> g(new Maze(NUMBER_OF_ROOMS + 2 * level_number));
	g->GenerateGraphStructure();

	return g;
}
