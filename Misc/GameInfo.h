#ifndef GAME_INFO
#define GAME_INFO

#include <chrono>
#include <string>

/* Class that stores all sort of informations on the game session */
class GameInfo
{
public :
  using clock = std::chrono::steady_clock;
  using time = std::chrono::time_point<clock>;
  using duration = std::chrono::duration<clock::rep,clock::period>;
  GameInfo();
  const time& getStartTime() const;
  duration GetElapsedTime() const;
  std::string GetFormattedElapsed() const;
private :

  time start_time;
};

#endif
