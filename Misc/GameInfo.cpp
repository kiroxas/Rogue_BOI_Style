#include "GameInfo.h"
#include "Constantes.h"

GameInfo::GameInfo() :
room_visited(0),
room_created(0)
{}

sf::Time GameInfo::GetElapsedTime() const
{
   return clock.getElapsedTime();
}

std::string GameInfo::GetFormattedElapsed() const
{
  auto sec = GetElapsedTime().asSeconds();
  return std::to_string(sec) + ":" + 
                  std::to_string(GetElapsedTime().asMilliseconds() - (sec * 1000));
}

 void GameInfo::setFps(float f)
{
   fps = f;
}

float GameInfo::getFps() const
{
   return fps;
}

 unsigned long long GameInfo::getRoomsVisited() const
 {
 	return room_visited;
 }

 void GameInfo::addVisited()
 {
 	++room_visited;
 }

 void GameInfo::dump() const
 {
 	static const std::string dump_p("dump.log");

 	infos::log(dump_p, "Rooms visited : " + std::to_string(room_visited));

 }
