#pragma once

#include <vector>
#include "LoginRequest.h"
#include "SignupRequest.h"

struct JsonRequestPacketDeserializer
{
	static LoginRequest deserializeLoginRequest(std::vector<char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<char> buffer);
};
std::string getBytes(int startPoint, int amount, std::vector<char> buffer);

int findStrIndex(std::string str, std::vector<char> buffer);
