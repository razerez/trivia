#include "JsonResponsePacketSerializer.h"



std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	
	std::vector<char> vec;
	vec.push_back('e'); //first byte of the protocol

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


std::vector<char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse logout)
{
	std::vector<char> vec;
	return vec;
}
