#include "HighscoreResponse.h"

HighscoreResponse::HighscoreResponse(int status, std::vector<HighscoreTable> highscores)
{
	this->_highscores = highscores;
	this->_status = status;
}

HighscoreResponse::~HighscoreResponse()
{
}
