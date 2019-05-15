#pragma once
#include <iostream>

struct RoomData
{
	int _id;
	std::string _name;
	std::string _maxPlayers;
	int _timePerQuestion;
	int _isActive;
//---------------------------
	RoomData(int id, std::string name, std::string maxPlayer, int timePerQuestion, int isActive);
	~RoomData();

};
