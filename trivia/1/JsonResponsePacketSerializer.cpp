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
	vec.push_back('o');
	vec.push_back(0b0);
	vec.push_back(0b0);
	vec.push_back(0b1);
	vec.push_back(char(logoutRes._status));
	return vec;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse roomRes)
{
	std::cout << "Sending rooms: ";
	std::string data = "{\nlength:" + std::to_string(roomRes._rooms.size()) + "\nRooms[";



	for (std::vector<RoomData>::iterator it = roomRes._rooms.begin(); it != roomRes._rooms.end(); ++it)
	{
		data += "\n\"" + (*it)._name + "\":" + std::to_string((*it)._id);
		std::cout << "-"<<(*it)._name << ":" << std::to_string((*it)._id);
	}

	std::cout << "-\n";

	data += "\n]\n}";

	std::vector<char> optionAndLenghVec;
	optionAndLenghVec.push_back('h');


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





std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse playerInRoomRes)
{
	
	std::string data = "{\nlength:" + std::to_string(playerInRoomRes._players.size()) + "\nNames[";

	std::cout << "Sending names: ";

	for (std::vector<std::string>::iterator it = playerInRoomRes._players.begin(); it != playerInRoomRes._players.end(); ++it)
	{
		data += "\n\"" + (*it) + "\"";
		std::cout << "-" << (*it);
	}

	std::cout << "-\n";

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
	
	std::string data = "{\nlength:" + std::to_string(highscoreRes._highscores.getHighscores().size()) + "\nHighscores[";
	
	map<LoggedUser*, int> mymap = highscoreRes._highscores.getHighscores();
	
	std::cout << "Sending highscors: ";

	for (std::map<LoggedUser*, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		data += "\n\"" + it->first->getUsername() + "\":" + std::to_string(it->second);
		std::cout << "-" << it->first->getUsername() << ":" << std::to_string(it->second);
	}

	std::cout << "-\n";

	data += "\n]\n}";

	std::vector<char> optionAndLenghVec;
	optionAndLenghVec.push_back('h');


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
