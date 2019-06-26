#include "RoomManager.h"


RoomManager::RoomManager()
{
	this->_m_counter = 0;
}

RoomManager::~RoomManager()
{
}

int RoomManager::joinRoom(LoggedUser loggedUsers, int room)
{
	try
	{
		this->_m_rooms.find(room)->second.addUser(loggedUsers);
		std::cout << loggedUsers.getUsername() << " join to the room: " << this->_m_rooms.find(room)->second.getRoomData()._name << std::endl;
		return 1;
	}
	catch (...)
	{
		return 0;
	}
}

int RoomManager::createRoom(LoggedUser loggedUsers, RoomData& roomData)
{
	try
	{
		this->_m_counter++;
		roomData._id = _m_counter;
		std::vector<LoggedUser> vec;
		vec.push_back(loggedUsers);
		this->_m_rooms.insert(std::pair<int, Room>(this->_m_counter, Room(roomData, vec)));
		std::cout<<"User " << loggedUsers.getUsername() << " Created The Room: " << roomData._name << std::endl;
		return 1;
	}
	catch (...)
	{
		return 0;
	}
}

int RoomManager::deleteRoom(int ID)
{
	try
	{
		this->_m_rooms.erase(ID);
		return 1;
	}
	catch (...)
	{
		return 0;
	}
}

int RoomManager::getRoomState(int ID)
{	
	return this->_m_rooms.find(ID)->second.getRoomData()._id;
}

Room RoomManager::getRoom(int ID)
{
	return this->_m_rooms.find(ID)->second;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> vec;
	for (std::map<int, Room>::iterator it = this->_m_rooms.begin(); it != this->_m_rooms.end(); ++it)
		vec.push_back(it->second.getRoomData());

	return vec;
}

std::vector<std::string> RoomManager::getPlayersInRooms(int Id)
{
	std::vector<LoggedUser> myUsers = this->_m_rooms.find(Id)->second.getAllUsers();
	std::vector<std::string> vec;
	
	for(std::vector<LoggedUser>::iterator it = myUsers.begin(); it != myUsers.end(); ++it)
	{
		vec.push_back((*it).getUsername());
	}
	return vec;
}


