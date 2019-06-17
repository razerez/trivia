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
	int _m_counter;
public:
	RoomManager();
	~RoomManager();

	void createRoom(LoggedUser loggedUsers, RoomData roomData);
	void deleteRoom(int ID);
	int getRoomState(int ID);
	std::vector<Room>getRooms();

};