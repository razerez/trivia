#pragma once

#include <vector>
#include "HighscoreTable.h"



struct HighscoreResponse
{
	int _status;
	std::vector<HighscoreTable> _highscores;
//-----------------------------------------
	HighscoreResponse(int status, std::vector<HighscoreTable> highscore);
	~HighscoreResponse();
};