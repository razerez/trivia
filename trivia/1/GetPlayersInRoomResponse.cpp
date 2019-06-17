#include "GetPlayersInRoomResponse.h"

GetPlayersInRoomResponse::GetPlayersInRoomResponse(std::vector<std::string> players)
{
	this->_players = players;
}

GetPlayersInRoomResponse::~GetPlayersInRoomResponse()
{
}
