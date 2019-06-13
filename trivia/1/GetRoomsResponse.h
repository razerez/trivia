#pragma once
#include <vector>
#include "RoomData.h"


struct GetRoomsResponse
{
	int _status;
	std::vector<RoomData> _rooms;
//----------------------------
	GetRoomsResponse(std::vector<RoomData> rooms, int status);
	~GetRoomsResponse();
};