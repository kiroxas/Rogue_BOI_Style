#ifndef IMAGE_POOL_H
#define IMAGE_POOL_H

#include <SFML/Graphics/Image.hpp>
#include <map>
#include <string>
#include "Constantes.h"

class ImagePool
{
  public : 
  
  ImagePool();
  const KiroGame::Image& getImage(const std::string& key);
  
  private :
  
  std::map<std::string, KiroGame::Image> pool;
};

#endif
