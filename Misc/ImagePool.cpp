#include "ImagePool.h"
#include <fstream>
#include "Constantes.h"
#include <string>

ImagePool::ImagePool()
{
	std::ifstream in(infos::pool_path);

	if(in.fail()) 
		return;

	std::string line;
	std::getline(in,line);

	while(!line.empty())
	{
		auto pos = line.find('\t');

		std::string id = line.substr(0,pos);
		std::string path = infos::sprite_path + line.substr(pos+1);

		sf::Image im;
		im.loadFromFile(path);

		pool[id] = std::move(im);
		std::getline(in,line);
	}
}