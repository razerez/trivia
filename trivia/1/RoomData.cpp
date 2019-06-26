#include "RoomData.h"

RoomData::RoomData(int id, std::string name, int maxPlayer, int timePerQuestion, int isActive, int questionCount)
{
	this->_id = id;
	this->_isActive = isActive;
	this->_maxPlayers = maxPlayer;
	this->_name = name;
	this->_timePerQuestion = timePerQuestion;
	this->_questionCount = questionCount;
}

RoomData::~RoomData()
{
}
