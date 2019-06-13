#include "GetPlayersInRoomResponse.h"

GetPlayersInRoomResponse::GetPlayersInRoomResponse(std::vector<std::string> rooms)
{
	this->_rooms = rooms;
}

GetPlayersInRoomResponse::~GetPlayersInRoomResponse()
{
}
