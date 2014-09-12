#ifndef GAME_INFO
#define GAME_INFO

#include <chrono>
#include <string>
#include <SFML/System/Clock.hpp>

/* Class that stores all sort of informations on the game session */
class GameInfo
{
public :
  GameInfo();
 
  sf::Time GetElapsedTime() const;
  std::string GetFormattedElapsed() const;
  void setFps(float);
  float getFps() const;
  unsigned long long getRoomsVisited() const;
  void addVisited();
  void dump() const;
private :

  sf::Clock clock;
  float fps;
  unsigned long long room_visited;
  unsigned long long room_created;
};

#endif
