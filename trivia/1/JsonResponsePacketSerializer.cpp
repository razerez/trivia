#include "JsonResponsePacketSerializer.h"

std::vector<char> serializeResponse(ErrorResponse err)
{
	/*
	std::vector<char> vec;
	vec.push_back('e'); //first byte of the protocol
	
	int length = err.message.length;
	char secondsByteLength = length & 0b11111111;
	length = length >> 8;
	char firstByteLength = length & 0b11111111;

	vec.push_back(firstByteLength);
	vec.push_back(secondsByteLength);
	for (int i = 0; i < err.message.length; i++)
	{
		vec.push_back(err.message[i]);
	}

	return vec;
	*/
	
	return std::vector<char>();
}

std::vector<char> serializeResponse(LoginResponse login)
{
	return std::vector<char>();
}

std::vector<char> serializeResponse(SignupResponse signup)
{
	return std::vector<char>();
}
