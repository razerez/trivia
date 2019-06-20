#pragma once

#include <vector>
#include "HighscoreTable.h"



struct HighscoreResponse
{
	int _status;
	HighscoreTable _highscores;
//-----------------------------------------
	HighscoreResponse(int status,HighscoreTable highscore);
	~HighscoreResponse();
};