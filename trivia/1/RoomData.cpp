#include "RoomData.h"

RoomData::RoomData(int id, std::string name, std::string maxPlayer, int timePerQuestion, int isActive)
{
	this->_id = id;
	this->_isActive = isActive;
	this->_maxPlayers = maxPlayer;
	this->_name = name;
	this->_timePerQuestion = timePerQuestion;

}

RoomData::~RoomData()
{
}
