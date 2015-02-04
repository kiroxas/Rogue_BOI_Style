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
  constexpr std::pair<int,int> room_pos(std::make_pair(0,100));
  constexpr std::pair<int,int> room_size(std::make_pair(800,500));
  constexpr std::pair<int,int> inner_room_pos(std::make_pair(60,160));
  constexpr std::pair<int,int> inner_room_size(std::make_pair(680,380));
  constexpr std::pair<int,int> map_placement(std::make_pair(0,0));
  constexpr std::pair<int,int> map_size(std::make_pair(400,100));
  constexpr std::pair<int,int> hub_pos(std::make_pair(map_placement.first + map_size.first,
                                                      0));
  constexpr std::pair<int,int> hub_size(std::make_pair(150,50));
  const sf::FloatRect RoomRect(room_pos.first,room_pos.second,room_size.first, room_size.second);
  const sf::FloatRect inner_RoomRect(inner_room_pos.first,
                                     inner_room_pos.second,
                                     inner_room_size.first,
                                     inner_room_size.second);
  const sf::FloatRect NorthWall(room_pos.first,
                                room_pos.second,
                                room_size.first,
                                inner_room_pos.second - room_pos.second);
  const sf::FloatRect SouthWall(room_pos.first, 
                                inner_room_pos.second + inner_room_size.second, 
                                room_size.first,
                                inner_room_pos.second);
  const sf::FloatRect EastWall(room_pos.first,
                               inner_room_pos.second,
                               inner_room_pos.first,
                               inner_room_size.second);
  const sf::FloatRect WestWall(inner_room_pos.first + inner_room_size.first,
                               inner_room_pos.second,
                               inner_room_pos.first,
                               inner_room_size.second);

  bool isInInnerRoom(const sf::FloatRect&);
};

#endif
