#include "GameInfo.h"

GameInfo::GameInfo() :
start_time(std::chrono::steady_clock::now())
{}

const GameInfo::time& GameInfo::getStartTime() const
{
   return start_time;
}

GameInfo::duration GameInfo::GetElapsedTime() const
{
   return clock::now() - start_time;
}

std::string GameInfo::GetFormattedElapsed() const
{
  auto ti = GetElapsedTime();
  auto sec = std::chrono::duration_cast<std::chrono::seconds>(ti);
  return std::to_string(sec.count()) + ":" + 
                  std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(ti).count() - (sec.count() * 1000));
}
