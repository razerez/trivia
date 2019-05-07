#include "JsonResponsePacketSerializer.h"

std::vector<char> serializeResponse(ErrorResponse)
{
	return std::vector<char>();
}

std::vector<char> serializeResponse(LoginResponse)
{
	return std::vector<char>();
}

std::vector<char> serializeResponse(SignupResponse)
{
	return std::vector<char>();
}
