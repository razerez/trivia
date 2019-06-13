#pragma once

#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>


class Room
{
	RoomData _m_metadata;
	std::vector<LoggedUser> _m_users;
public:
	Room();
	~Room();
	void addUser();
	void deleteUser();
	void getAllUsers();


};