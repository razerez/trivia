#include "GameData.h"



GameData::GameData(Question currectQuestion, int currectAnswerCount, int wrongAnswerCount, int averangeAnswerTime) : _currectQuestion(currectQuestion)
{
	this->_currectAnswerCount = currectAnswerCount;
	this->_wrongAnswerCount = wrongAnswerCount;
	this->_averangeAnswerTime = averangeAnswerTime;
}

GameData::~GameData()
{
}
