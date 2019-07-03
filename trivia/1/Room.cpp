#include "Room.h"

std::mutex mutexLock;

Room::Room(RoomData m_metadata, std::vector<LoggedUser> m_users) : _m_metadata(m_metadata)
{
	this->_m_users = m_users;
}

Room::~Room()
{
}

void Room::addUser(LoggedUser user)
{
	std::unique_lock<std::mutex> myLock(mutexLock);
	this->_m_users.push_back(user);
	mutexLock.unlock();

}

void Room::deleteUser(LoggedUser user)
{
	std::string username = user.getUsername();
	bool flag = true;
	int counter = 0;

	for (std::vector<LoggedUser>::iterator i = this->_m_users.begin(); i != this->_m_users.end() && flag; ++i)
	{
		if ((*i).getUsername() == username)
		{
			flag = !flag;
			counter--;
		}
		counter++;
	}
	std::unique_lock<std::mutex> myLock(mutexLock);
	this->_m_users.erase(this->_m_users.begin() + counter);
	mutexLock.unlock();
}

std::vector<LoggedUser> Room::getAllUsers()
{
	std::unique_lock<std::mutex> myLock(mutexLock);
	return this->_m_users;
}

RoomData Room::getRoomData() const
{
	std::unique_lock<std::mutex> myLock(mutexLock);
	return this->_m_metadata;
}

void Room::startGame()
{
	std::unique_lock<std::mutex> myLock(mutexLock);
	this->_m_metadata._isActive = 1;
	mutexLock.unlock();
}

