#include "RoomFactory.h"

std::unique_ptr<Room> RoomFactory::CreateRoom(RoomType type,unsigned int number,const ImagePool& p)
{
	return std::unique_ptr<Room>(new Room(type, number,p));
}
