#ifndef GAME_INFO
#define GAME_INFO

#include <chrono>
#include <string>
#include <SFML/System/Clock.hpp>

/* Class that stores all sort of informations on the game session */
class GameInfo
{
public :
 
  sf::Time GetElapsedTime() const;
  std::string GetFormattedElapsed() const;
  void setFps(float);
  float getFps() const;
  unsigned long long getRoomsVisited() const;
  void addVisited();
  void addCreated(unsigned long long);
  void addEnnemiesEncountered(unsigned long long);
  void dump() const;
private :

  sf::Clock clock;
  float fps;
  unsigned long long room_visited = 0;
  unsigned long long room_created = 0;
  unsigned long long ennemies_encountered = 0;
};

#endif
