#include "GameInfo.h"

GameInfo::GameInfo()
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
