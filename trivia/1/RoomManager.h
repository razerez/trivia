#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "LoggedUser.h"
#include "Room.h"
#include "RoomData.h"

class RoomManager
{
	std::map<int, Room> _m_rooms;
public:
	RoomManager(std::map<int, Room> m_rooms);
	~RoomManager();

	void createRoom(LoggedUser loggedUsers);
	void deleteRoom();
	int getRoomState(int ID);
	std::vector<RoomData>getRooms();

};