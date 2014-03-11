#ifndef ROOM_FACTORY_H
#define ROOM_FACTORY_H

#include <memory>
#include "Room.h"
#include "../Misc/ImagePool.h"

class RoomFactory
{
public :
	//VirtualFunctions
	virtual std::unique_ptr<Room> CreateRoom(RoomType,unsigned int,const ImagePool&);
};

#endif
