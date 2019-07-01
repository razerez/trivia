#include "GetRoomStateResponse.h"

GetRoomStateResponse::GetRoomStateResponse(int status, bool hasGameBegun, std::vector<std::string> players, int questionCount, int answerTimeount)
{
	this->_status = status;
	this->_questionCount = questionCount;
	this->_answerTimeount = answerTimeount;
	this->_hasGameBegun = hasGameBegun;
	this->_players = players;
}

GetRoomStateResponse::~GetRoomStateResponse()
{
}
