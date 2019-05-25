#pragma once

#include <algorithm>
#include <vector>
#include "LoginRequest.h"
#include "SignupRequest.h"

struct JsonRequestPacketDeserializer
{
	static LoginRequest deserializeLoginRequest(std::vector<char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<char> buffer);
};
std::string getBytes(int skipTo, int dataSize, std::vector<char> buffer);

size_t findStrIndex(std::string str, std::vector<char> buffer, int startPoint);
