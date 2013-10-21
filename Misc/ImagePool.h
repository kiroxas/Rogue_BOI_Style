#ifndef IMAGE_POOL_H
#define IMAGE_POOL_H

#include <SFML/Graphics/Image.hpp>
#include <map>
#include <string>

namespace KiroGame
{
  struct Image
  {
    sf::Image image;
    std::string info_path;
  };
};

class ImagePool
{
  public : 
  
  ImagePool();
  const Image& getImage(const std::string& key);
  
  private :
  
  std::map<std::string,Image> pool;
};

#endif
