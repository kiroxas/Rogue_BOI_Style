#include "Stringpool.h"
#include <iostream>
#include <fstream>


int wstringToInt(const std::wstring& chaine) // TODO, template, needs to happen at compile time
{
	static int cpt = 0;
	return cpt++;
}

void Stringpool::setLanguage(Language l)
{
	active_language = l;
}

Stringpool::Stringpool(const std::string& path) :
	active_language(Language::English)
{
	std::wifstream in(path);

	if(in.fail()) 
		return;

	std::wstring line;
	std::getline(in,line);

	while(!line.empty())
	{
		auto pos = line.find(L"'");
		auto pos2 = line.find(L"'", pos+1);

		std::wstring ind = line.substr(pos+1, pos2-1-pos);
		pos = line.find(L"'", pos2+1);

		while(pos != std::wstring::npos)
		{
			pos2 = line.find(L"'", pos+1);
			pool[ind].push_back(line.substr(pos+1,pos2-1-pos));
			pos = line.find(L"'", pos2+1);
		}
		std::getline(in,line);
	}
}

std::wstring Stringpool::getString(std::wstring ind)
{
	return pool[ind][active_language];
}