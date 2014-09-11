#include "Constantes.h"

#include <fstream>

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

bool KiroGame::isInInnerRoom(const sf::FloatRect& rec)
{
	return !rec.intersects(NorthWall) &&
		   !rec.intersects(SouthWall) &&
		   !rec.intersects(EastWall) &&
		   !rec.intersects(WestWall) &&
		    rec.intersects(inner_RoomRect);
}
