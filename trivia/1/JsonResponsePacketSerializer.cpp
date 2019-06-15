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

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutRes)
{
	return std::vector<char>('x');
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse roomRes)
{
	std::vector<char> vec;
	vec.push_back('g');
	vec.push_back(0b1);
	vec.push_back(char(roomRes._status));
	vec.push_back(roomRes._rooms.size());
	vec.push_back('-');
	std::vector<RoomData>::iterator it;
	for (it = roomRes._rooms.begin(); it != roomRes._rooms.end(); ++it)
	{
		vec.push_back((*it)._id);
		vec.push_back(';');
		vec.push_back((*it)._isActive);
		vec.push_back(';');
		
		for (int i = 0; i < (*it)._maxPlayers.size(); i++)
		{
			vec.push_back((*it)._maxPlayers[i]);
		}
		vec.push_back(';');
		
		for (int i = 0; i < (*it)._name.size(); i++)
		{
			vec.push_back((*it)._name[i]);
		}
		vec.push_back(';');

		vec.push_back((*it)._timePerQuestion);
	}
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializerResponse(GetPlayersInRoomResponse playerInRoomRes)
{
	std::vector<char> vec;
	vec.push_back('p');
	vec.push_back(playerInRoomRes._players.size());
	vec.push_back(';');
	std::vector<std::string>::iterator it;
	for (it = playerInRoomRes._players.begin(); it != playerInRoomRes._players.end(); ++it)
	{
		for (int i = 0; i < (*it).size(); i++)
		{
			vec.push_back((*it)[i]);
		}
		vec.push_back(';');
	}

	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse roomRes)
{
	std::vector<char> vec;
	vec.push_back(0b1);
	vec.push_back(roomRes._status);
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomRes)
{
	std::vector<char> vec;
	vec.push_back(0b1);
	vec.push_back(createRoomRes._status);
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(HighscoreResponse highscoreRes)
{
	return std::vector<char>();
}
