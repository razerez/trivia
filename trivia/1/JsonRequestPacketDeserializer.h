#pragma once

#include <algorithm>
#include <vector>
#include "LogoutRequest.h"
#include "LoginRequest.h"
#include "SignupRequest.h"
#include "GetPlayersInRoomRequest.h"
#include "JoinRoomRequest.h"
#include "CreateRoomRequest.h"
#include "SubmitAnswerRequest.h"




struct JsonRequestPacketDeserializer
{
	LogoutRequest deserializeLogoutRequest(std::vector<char> buffer);
	LoginRequest deserializeLoginRequest(std::vector<char> buffer);
    SignupRequest deserializeSignupRequest(std::vector<char> buffer);

	GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<char> buffer);
	JoinRoomRequest deserializeJoinRoomRequest(std::vector<char> buffer);
	CreateRoomRequest deserializeCreateRoomRequest(std::vector<char> buffer);
	SubmitAnswerRequest deserializeSubmitAnswerRequest(std::vector<char> buffer);


private:
	std::string analyzeJson(std::vector<char> buffer, std::string subject, int dataLocation, int sizeLocation, int sizeLength);
	int _dataLocationSign;
};

std::string getBytes(int skipTo, int dataSize, std::vector<char> buffer);

size_t findStrIndex(std::string str, std::vector<char> buffer, int startPoint);
