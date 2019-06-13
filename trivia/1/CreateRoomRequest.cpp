#include "CreateRoomRequest.h"

CreateRoomRequest::CreateRoomRequest(std::string roomName, int maxUsers, int questionCount, int answerTimeout)
{
	this->answerTimeout = answerTimeout;
	this->maxUsers = maxUsers;
	this->questionCount = questionCount;
	this->roomName = roomName;
}

CreateRoomRequest::~CreateRoomRequest()
{
}
