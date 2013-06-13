#ifndef STRINGPOOL_H
#define STRINGPOOL_H

#include <string>
#include <map>
#include <vector>

class Stringpool
{
public :

	Stringpool(const std::string& path);
	std::wstring getString(std::size_t);

private :

	std::map<int,std::vector<std::wstring>> pool;
	std::size_t active_language;
};

#endif