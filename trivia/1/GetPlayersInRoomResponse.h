#pragma once

#include <iostream>
#include <vector>

struct GetPlayersInRoomResponse
{

	std::vector<std::string> _players;
//------------------------------
	GetPlayersInRoomResponse(std::vector<std::string> players);
	~GetPlayersInRoomResponse();

};