#include "Room.h"

Room::Room(RoomData m_metadata, std::vector<LoggedUser> m_users) : _m_metadata(m_metadata)
{
	this->_m_users = m_users;
}

Room::~Room()
{
}

void Room::addUser(LoggedUser user)
{
	this->_m_users.push_back(user);

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
	
	this->_m_users.erase(this->_m_users.begin() + counter);
	std::cout << username << " Logged Out" << std::endl;
}

std::vector<LoggedUser> Room::getAllUsers()
{
	return this->_m_users;
}

RoomData Room::getRoomData() const
{
	return this->_m_metadata;
}

