#include "JsonResponsePacketSerializer.h"



std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	
	std::vector<char> vec;
	vec.push_back('e');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b0);

	return vec;
	
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse login)
{
	std::vector<char> vec;
	vec.push_back('i');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(char(login._status));
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse signup)
{
	std::vector<char> vec;
	vec.push_back('u');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(char(signup._status));
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutRes)
{
	std::vector<char> vec;
	vec.push_back('x');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b0);
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse roomRes)
{
	
	std::vector<char> vec;
	/*
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
	*/
	return vec;
	
}





std::vector<char> JsonResponsePacketSerializer::serializerResponse(GetPlayersInRoomResponse playerInRoomRes)
{
	
	std::string data = "{\nlength:" + std::to_string(playerInRoomRes._players.size()) + "\nNames:[";



	for (std::vector<std::string>::iterator it = playerInRoomRes._players.begin(); it != playerInRoomRes._players.end(); ++it)
	{
		data += "\n\"" + (*it) + "\"";
	}
	data += "\n]\n}";

	std::vector<char> optionAndLenghVec;
	optionAndLenghVec.push_back('p');

	int size = data.size();
	
	optionAndLenghVec.push_back(0b0);

	char leftByte = size >> 8;
	char rightByte = size & 0b0000000011111111;

	optionAndLenghVec.push_back(leftByte);
	optionAndLenghVec.push_back(rightByte);
	

	std::vector<char> dataVector = stringToVectorChar(data);

	optionAndLenghVec.insert(optionAndLenghVec.end(), dataVector.begin(), dataVector.end());
	
	return optionAndLenghVec;
	
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse roomRes)
{
	
	std::vector<char> vec;
	vec.push_back('j');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(roomRes._status);
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomRes)
{
	std::vector<char> vec;
	vec.push_back('c');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(createRoomRes._status);
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(HighscoreResponse highscoreRes)
{
	return std::vector<char>();
}
