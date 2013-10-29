#ifndef IMAGE_POOL_H
#define IMAGE_POOL_H

#include <map>
#include <string>
#include <vector>
#include "Constantes.h"

class ImagePool
{
  public : 
  
  ImagePool();
  const KiroGame::Image& getImage(const std::string& key) const;
  std::vector<std::string> getImagesName();
  
  private :
  
  std::map<std::string, KiroGame::Image> pool;
};

#endif
