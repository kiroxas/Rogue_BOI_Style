#include "RoomFactory.h"

std::unique_ptr<Room> RoomFactory::CreateRoom(RoomType type,unsigned int number)
{
	return std::unique_ptr<Room>(new Room(type, number));
}