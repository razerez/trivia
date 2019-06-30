#pragma once

#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>
#include <string>

class Room
{
	RoomData _m_metadata;
	std::vector<LoggedUser> _m_users;
public:
	Room(RoomData m_metadata, std::vector<LoggedUser> m_users);
	~Room();
	void addUser(LoggedUser user);
	void deleteUser(LoggedUser user);
	std::vector<LoggedUser> getAllUsers();
	RoomData getRoomData() const;
	void startGame();


};