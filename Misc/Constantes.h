#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <string>
#include <Graphics.hpp>

#define VERBOSE 
#define MAZE_LOG_PATH "Maze_Generation.log"
#define RENDERING_PATH "Rendering.log"
#define NUMBER_OF_ROOMS 5

namespace infos
{
	const std::string sprite_path("Rogue_BOI_Style//data//sprite Sheets//");
	const std::string pool_path(sprite_path + "pool_image.txt");
	bool log(const std::string& path, const std::string& message, bool new_line = true);
}

namespace KiroGame
{
  struct Image
  {
    sf::Image image;
    std::string info_path;
  };
};

#endif
