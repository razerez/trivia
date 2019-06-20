#include "HighscoreResponse.h"


HighscoreResponse::HighscoreResponse(int status, HighscoreTable highscore): _highscores(highscore)
{
	this->_status = status;
}

HighscoreResponse::~HighscoreResponse()
{
}
