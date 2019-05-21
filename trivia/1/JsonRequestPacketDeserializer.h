#pragma once

#include <vector>
#include "LoginRequest.h"
#include "SignupRequest.h"

struct JsonRequestPacketDeserializer
{
	static LoginRequest deserializeLoginRequest(std::vector<char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<char> buffer);
};
