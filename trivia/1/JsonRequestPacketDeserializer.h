#pragma once

#include <vector>
#include "LoginRequest.h"
#include "SignupRequest.h"

/*
only here this is cant be until we build buffer.
*/
struct JsonRequestPacketDeserializer
{
	static LoginRequest deserializeLoginRequest(std::vector<char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<char> buffer);
};