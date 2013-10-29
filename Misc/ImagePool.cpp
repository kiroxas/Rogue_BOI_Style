#include "ImagePool.h"
#include <fstream>
#include "Constantes.h"
#include <string>
#include <iostream>

ImagePool::ImagePool()
{
	std::ifstream in(infos::pool_path);

	if(in.fail()) 
	{
		std::cerr << "Unable to open " + infos::pool_path << std::endl;
		return;
	}

	std::string line;
	std::getline(in,line);

	while(!line.empty())
	{
		KiroGame::Image m;
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

std::vector<std::string> ImagePool::getImagesName()
{
	std::vector<std::string> res;
	for(auto e : pool)
		res.push_back(e.first);

	return res;
}

const KiroGame::Image& ImagePool::getImage(const std::string& key) const
{
	return pool.at(key);
}
