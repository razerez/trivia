#pragma once
#include <iostream>

struct RoomData
{
	int _id;
	std::string _name;
	int _maxPlayers;
	int _timePerQuestion;
	int _isActive;
//---------------------------
	RoomData(int id, std::string name, int maxPlayer, int timePerQuestion, int isActive);
	~RoomData();

};
