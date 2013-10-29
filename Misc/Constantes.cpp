#include "Constantes.h"

#pragma warning(push, 0)
#include <fstream>
#pragma warning(pop)

bool infos::log(const std::string& path, const std::string& message, bool new_line)
{
#ifdef VERBOSE
	std::ofstream log(path.c_str(),std::ios_base::app);

	if(log.fail()) return false;

	log << message;
	if(new_line) log << std::endl;
#endif
	return true;
}