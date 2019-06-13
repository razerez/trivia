#include "RoomManager.h"

RoomManager::RoomManager(std::map<int, Room> m_rooms)
{
	this->_m_rooms = _m_rooms;
}

RoomManager::~RoomManager()
{
}

void RoomManager::createRoom(LoggedUser loggedUsers)
{
}

void RoomManager::deleteRoom()
{
}

int RoomManager::getRoomState(int ID)
{
	return 0;
}

std::vector<RoomData> RoomManager::getRooms()
{
	return std::vector<RoomData>();
}


