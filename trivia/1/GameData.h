#pragma once

#include "Question.h"

struct GameData
{
	Question _currectQuestion;
	int _currectAnswerCount;
	int _wrongAnswerCount;
	int _averangeAnswerTime;
//-----------------------------------
	GameData(Question currectQuestion, int currectAnswerCount, int wrongAnswerCount, int averangeAnswerTime);
	~GameData();


};

