#include "GetRoomStateResponse.h"

GetRoomStateResponse::GetRoomStateResponse(int status, bool haGameBegun, std::vector<std::string> players, int questionCount, int answerTimeCount)
{
	this->_status = status;
	this->_questionCount = questionCount;
	this->_answerTimeCount = answerTimeCount;
	this->_hasGameBegun = _hasGameBegun;
	this->_players = players;
}

GetRoomStateResponse::~GetRoomStateResponse()
{
}
