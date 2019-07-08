#include "RoomManager.h"


std::mutex mutexLockRoomManager;

RoomManager::RoomManager()
{
	this->_m_counter = 0;
}

RoomManager::~RoomManager()
{
}

int RoomManager::joinRoom(LoggedUser loggedUsers, int room)
{

	std::unique_lock<std::mutex> myLock(mutexLockRoomManager);
	if (this->_m_rooms.find(room) == this->_m_rooms.end()) 
	{
		return 0;
	}
	myLock.unlock();
	try
	{
		myLock.lock();
		//    for example the ([size is 2 (2 players connected)]    <    [max players = 3]) its work and it will add player
		//    for example the ([size is 3 (3 players connected)]    <    [max players = 3]) its dont work and it will not add player
		if (this->_m_rooms.find(room)->second.getAllUsers().size() < this->_m_rooms.find(room)->second.getRoomData()._maxPlayers)
		{
			this->_m_rooms.find(room)->second.addUser(loggedUsers);
			std::cout << loggedUsers.getUsername() << " Joined The Room: " << this->_m_rooms.find(room)->second.getRoomData()._name << std::endl;
			return 1;
		}
		myLock.unlock();
		return 0;
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
		std::unique_lock<std::mutex> myLock(mutexLockRoomManager);
		this->_m_counter++;
		roomData._id = _m_counter;
		std::vector<LoggedUser> vec;
		vec.push_back(loggedUsers);
		this->_m_rooms.insert(std::pair<int, Room>(this->_m_counter, Room(roomData, vec)));
		myLock.unlock();
		std::cout << "User " << loggedUsers.getUsername() << " Created The Room: " << roomData._name << std::endl;
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
		std::unique_lock<std::mutex> myLock(mutexLockRoomManager);
		this->_m_rooms.erase(ID);
		myLock.unlock();
		return 1;
	}
	catch (...)
	{
		return 0;
	}
}

int RoomManager::getRoomState(int ID)
{
	std::unique_lock<std::mutex> myLock(mutexLockRoomManager);
	return this->_m_rooms.find(ID)->second.getRoomData()._id;
}

Room * RoomManager::getRoom(int ID)
{
	std::unique_lock<std::mutex> myLock(mutexLockRoomManager);
	return &this->_m_rooms.find(ID)->second;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> vec;
	std::unique_lock<std::mutex> myLock(mutexLockRoomManager);
	for (std::map<int, Room>::iterator it = this->_m_rooms.begin(); it != this->_m_rooms.end(); ++it)
		vec.push_back(it->second.getRoomData());
	myLock.unlock();
	return vec;
}

std::vector<std::string> RoomManager::getPlayersInRooms(int Id)
{
	std::unique_lock<std::mutex> myLock(mutexLockRoomManager);
	if (this->_m_rooms.find(Id) == this->_m_rooms.end())
	{
		return std::vector<std::string>();
	}
	std::vector<LoggedUser> myUsers = this->_m_rooms.find(Id)->second.getAllUsers();
	myLock.unlock();
	std::vector<std::string> vec;

	for (std::vector<LoggedUser>::iterator it = myUsers.begin(); it != myUsers.end(); ++it)
	{
		vec.push_back((*it).getUsername());
	}
	return vec;
}