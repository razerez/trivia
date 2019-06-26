#pragma once
#include <iostream>

struct RoomData
{
	int _id;
	std::string _name;
	int _maxPlayers;
	int _timePerQuestion;
	int _isActive;
	int _questionCount;
//---------------------------
	RoomData(int id, std::string name, int maxPlayer, int timePerQuestion, int isActive, int questionCount);
	~RoomData();

};
