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
		Image m;
		auto pos = line.find('\t');

		std::string id = line.substr(0,pos);
		auto pos2 = line.find('\t',pos);
		std::string path = infos::sprite_path + line.substr(pos+1,pos2);

		m.image.loadFromFile(path);
		m.info_path = line.substr(pos2);

		pool[id] = m;
		std::getline(in,line);
	}
}
