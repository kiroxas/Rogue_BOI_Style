#ifndef STRINGPOOL_H
#define STRINGPOOL_H

#include <string>
#include <map>
#include <vector>

enum Language
{
	English = 0, 
	French,
	Japanese
};

class Stringpool
{
public :

	Stringpool(const std::string& path);
	std::wstring getString(std::wstring);
	void setLanguage(Language);

private :

	std::map<std::wstring,std::vector<std::wstring>> pool;
	std::size_t active_language;
};

#endif