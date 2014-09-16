#include "GameInfo.h"
#include "Constantes.h"

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

 	infos::log(dump_p, "Rooms Visited : " + std::to_string(room_visited));
 	infos::log(dump_p, "Rooms Created : " + std::to_string(room_created));
 	infos::log(dump_p, "Ennemies : " + std::to_string(ennemies_encountered));
 	infos::log(dump_p, "Ennemies killed : " + std::to_string(killed_ennemies));
 }

 void GameInfo::addCreated(unsigned long long n)
 {
 	room_created += n;
 }

void GameInfo::addEnnemiesEncountered(unsigned long long n)
{
	ennemies_encountered += n;
}

void GameInfo::KilledAnEnnemy()
{
	killed_ennemies++;
}