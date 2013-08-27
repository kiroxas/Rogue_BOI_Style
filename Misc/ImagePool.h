#ifndef IMAGE_POOL_H
#define IMAGE_POOL_H

#include <SFML/Graphics/Image.hpp>
#include <map>
#include <string>

class ImagePool
{
  public : 
  
  ImagePool();
  const sf::Image& getImage(const std::string& key);
  
  private :
  
  std::map<std::string,sf::Image> pool;
};

#endif
