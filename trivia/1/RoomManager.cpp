#include "RoomManager.h"


RoomManager::RoomManager()
{
	this->_m_counter = 0;
}

RoomManager::~RoomManager()
{
}

void RoomManager::createRoom(LoggedUser loggedUsers, RoomData roomData)
{
	this->_m_counter++;
	std::vector<LoggedUser> vec;
	vec.push_back(loggedUsers);
	this->_m_rooms.insert(std::pair<int, Room>(this->_m_counter, Room(roomData, vec)));
}

void RoomManager::deleteRoom(int ID)
{
	this->_m_rooms.erase(ID);
}

int RoomManager::getRoomState(int ID)
{	
	return this->_m_rooms.find(ID)->second.getRoomData()._id;
}

std::vector<Room> RoomManager::getRooms()
{
	return std::vector<Room>();
}


