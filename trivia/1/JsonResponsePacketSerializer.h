#pragma once
#include <bitset>
#include <string>
#include "Vector and string.h"
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
#include "CloseRoomResponse.h"
#include "StartGameResponse.h"
#include "GetRoomStateResponse.h"
#include "LeaveRoomResponse.h"
#include "MyStatusResponse.h"
#include <vector>


struct JsonResponsePacketSerializer
{
	static std::vector<char> serializeResponse(ErrorResponse errorRes);
	static std::vector<char> serializeResponse(LoginResponse loginRes);
	static std::vector<char> serializeResponse(SignupResponse signupRes);
	static std::vector<char> serializeResponse(LogoutResponse logoutRes);
	static std::vector<char> serializeResponse(GetRoomsResponse roomRes);
	static std::vector<char> serializeResponse(GetPlayersInRoomResponse playerInRoomRes);
	static std::vector<char> serializeResponse(JoinRoomResponse roomRes);
	static std::vector<char> serializeResponse(CreateRoomResponse createRoomRes);
	static std::vector<char> serializeResponse(HighscoreResponse highscoreRes);
	static std::vector<char> serializeResponse(CloseRoomResponse closeRoomRes);
	static std::vector<char> serializeResponse(StartGameResponse startGameRes);
	static std::vector<char> serializeResponse(GetRoomStateResponse getRoomStatRes);
	static std::vector<char> serializeResponse(LeaveRoomResponse leaveRoomRes);
	static std::vector<char> serializeResponse(MyStatusResponse myStatus);

};