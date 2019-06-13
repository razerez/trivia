#include "Room.h"

Room::Room(RoomData m_metadata, std::vector<LoggedUser> m_users) : _m_metadata(m_metadata)
{
	this->_m_users = m_users;
}

void Room::addUser()
{
}

void Room::deleteUser()
{
}

void Room::getAllUsers()
{
}
