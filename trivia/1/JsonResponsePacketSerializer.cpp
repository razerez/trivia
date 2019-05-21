#include "JsonResponsePacketSerializer.h"



std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	
	std::vector<char> vec;
	vec.push_back('e'); //first byte of the protocol

	int length = err.message.length();
	char secondsByteLength = length & 0b11111111;
	length = length >> 8;
	char firstByteLength = length & 0b11111111;

	vec.push_back(firstByteLength);
	vec.push_back(secondsByteLength);
	for (int i = 0; i < err.message.length(); i++)
	{
		vec.push_back(err.message[i]);
	}

	return vec;
	
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse login)
{
	std::vector<char> vec;
	vec.push_back('i'); //first byte of the protocol
	vec.push_back(0b00000001);
	vec.push_back(char(login._status));
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse signup)
{
	std::vector<char> vec;
	vec.push_back('u');
	vec.push_back(0b00000001);
	vec.push_back(char(signup._status));
	return vec;
}
