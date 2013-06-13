#include "Stringpool.h"
#include <iostream>
#include <fstream>


int wstringToInt(const std::wstring& chaine) // TODO, template, needs to happen at compile time
{
	static int cpt = 0;
	return cpt++;
}

Stringpool::Stringpool(const std::string& path) :
	active_language(1)
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

		int ind = wstringToInt(line.substr(pos+1, pos2-1-pos));
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