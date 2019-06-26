#pragma once

#include <iostream>
#include <string>

struct CreateRoomRequest
{
	std::string roomName;
	int maxUsers;
	int questionCount;
	int answerTimeout;
//-----------------------
	CreateRoomRequest(std::string roomName, int maxUsers, int questionCount, int answerTimeout);
	~CreateRoomRequest();
};