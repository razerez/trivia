#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

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

	int joinRoom(LoggedUser loggedUsers, int room);
	int createRoom(LoggedUser loggedUsers, RoomData roomData);
	int deleteRoom(int ID);
	int getRoomState(int ID);
	std::vector<std::string>getPlayersInRooms(int Id);

};