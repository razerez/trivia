#pragma once

#include <iostream>
#include <vector>

struct GetPlayersInRoomResponse
{

	std::vector<std::string> _rooms;
//------------------------------
	GetPlayersInRoomResponse(std::vector<std::string> rooms);
	~GetPlayersInRoomResponse();

};