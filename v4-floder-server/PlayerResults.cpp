#include "PlayerResults.h"

PlayerResults::PlayerResults(std::string username, int correctAnswerCount, int wrongAnswerCount, int avergeAnswerTime)
{
	this->_averageAnswerTime = avergeAnswerTime;
	this->_correctAnswerCount = correctAnswerCount;
	this->_username = username;
	this->_wrongAnswerCount = wrongAnswerCount;
}

PlayerResults::~PlayerResults()
{
}
