#pragma once


struct GetPlayersInRoomRequest
{
	int roomId;
	//-------------
	GetPlayersInRoomRequest(int roomId);
	~GetPlayersInRoomRequest();
};