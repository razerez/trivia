#pragma once
#include "ErrorResponse.h"
#include "Communicator.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include "LogoutResponse.h"
#include "GetRoomsResponse.h"
#include "GetPlayersInRoomResponse.h"
#include "JoinRoomResponse.h"
#include "CreateRoomResponse.h"
#include "HighscoreResponse.h"

#include <vector>


struct JsonResponsePacketSerializer
{
	static std::vector<char> serializeResponse(ErrorResponse err);
	static std::vector<char> serializeResponse(LoginResponse login);
	static std::vector<char> serializeResponse(SignupResponse signup);
	static std::vector<char> serializeResponse(LogoutResponse logoutRes);
	static std::vector<char> serializeResponse(GetRoomsResponse roomRes);
	static std::vector<char> serializerResponse(GetPlayersInRoomResponse playerInRoomRes);
	static std::vector<char>serializeResponse(JoinRoomResponse roomRes);
	static std::vector<char>serializeResponse(CreateRoomResponse createRoomRes);
	static std::vector<char>serializeResponse(HighscoreResponse highscoreRes);
};