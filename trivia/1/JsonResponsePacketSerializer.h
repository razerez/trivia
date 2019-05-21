#pragma once
#include "ErrorResponse.h"
#include "Communicator.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include <vector>


struct JsonResponsePacketSerializer
{
	static std::vector<char> serializeResponse(ErrorResponse err);
	static std::vector<char> serializeResponse(LoginResponse login);
	static std::vector<char> serializeResponse(SignupResponse signup);
};