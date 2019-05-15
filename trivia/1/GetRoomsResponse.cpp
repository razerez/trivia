#include "GetRoomsResponse.h"

GetRoomsResponse::GetRoomsResponse(std::vector<RoomData> rooms, int status)
{
	this->_rooms = rooms;
	this->_status = status;
}

GetRoomsResponse::~GetRoomsResponse()
{
}
