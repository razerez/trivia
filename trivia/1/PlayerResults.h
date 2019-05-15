#pragma once

#include <iostream>

struct PlayerResults
{
	std::string _username;
	int _correctAnswerCount;
	int _wrongAnswerCount;
	int _averageAnswerTime;
//------------------------------------
	PlayerResults(std::string username, int correctAnswerCount, int wrongAnswerCount, int avergeAnswerTime);
	~PlayerResults();
};