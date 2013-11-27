#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <string>
#include <SFML/Graphics.hpp>
#include <utility>

#define VERBOSE 
#define MAZE_LOG_PATH "Maze_Generation.log"
#define RENDERING_PATH "Rendering.log"
#define NUMBER_OF_ROOMS 5

namespace infos
{
	const std::string sprite_path("./data/sprite Sheets/");
	const std::string pool_path(sprite_path + "pool_image.txt");
	bool log(const std::string& path, const std::string& message, bool new_line = true);
}

enum Direction{ SOUTH = 0, NORTH,EAST,WEST};

namespace KiroGame
{
  struct Image
  {
    sf::Image image;
    std::string info_path;
  };

  const sf::Color transparent(0,255,0);
  const sf::Time elapsed_animation_time = sf::seconds(0.08);
  const std::pair<int,int> room_pos(std::make_pair(0,100));
  const std::pair<int,int> room_size(std::make_pair(800,500));
  const sf::FloatRect RoomRect(room_pos.first,room_pos.second,room_size.first,room_size.second);
};

#endif
