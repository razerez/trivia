#include "JsonRequestPacketDeserializer.h"

#define CODE_SEGMENT 1
#define LOGIN_DATA_SIZE_SEGMENT 2
#define USERNAME_SIZE_SEGMENT 1
#define PASSWORD_SIZE_SEGMENT 1
#define LENGTH_SEGMENT 3
#define EMAIL_SIZE_SEGMENT 1

LogoutRequest JsonRequestPacketDeserializer::deserializeLogoutRequest(std::vector<char> buffer)
{
	//  std::string username = analyzeJson(buffer, "username:" 5, 4, 1)
	std::string username = analyzeJson(buffer, "username:", LENGTH_SEGMENT + LOGIN_DATA_SIZE_SEGMENT, CODE_SEGMENT + LENGTH_SEGMENT, USERNAME_SIZE_SEGMENT);
	LogoutRequest myLogout(username);
	return myLogout;
}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char> buffer)
{
	LogoutRequest myLogout = deserializeLogoutRequest(buffer);
	std::string username = myLogout._username;
	std::string password = analyzeJson(buffer, "password:", this->_dataLocation , CODE_SEGMENT + LENGTH_SEGMENT + USERNAME_SIZE_SEGMENT, PASSWORD_SIZE_SEGMENT);
	LoginRequest myLogin(username, password);
	return myLogin;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<char> buffer)
{
	LoginRequest myLogin = deserializeLoginRequest(buffer);
	std::string username = myLogin._username;
	std::string password = myLogin._password;
	std::string email = analyzeJson(buffer, "email:", this->_dataLocation, CODE_SEGMENT + LENGTH_SEGMENT + USERNAME_SIZE_SEGMENT + PASSWORD_SIZE_SEGMENT, EMAIL_SIZE_SEGMENT);

	SignupRequest mySignup(username, password, email);
	return mySignup;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<char> buffer)
{
	return GetPlayersInRoomRequest(int(buffer[4]));;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<char> buffer)
{
	
	return JoinRoomRequest(int(buffer[4]));;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<char> buffer)
{
	return CreateRoomRequest("", 0,0,0);
}



std::string JsonRequestPacketDeserializer::analyzeJson(std::vector<char> buffer, std::string subject, int dataLocation, int sizeLocation, int sizeLength)
//input: buffer, keyWord to search in json, locationOfTheKeyWord, location of the size of the segment, the length of this size
//returns analyzed string from json and insert next dataLocation into this->_dataLocation
{
	int size = buffer[sizeLocation];
	int keyIndex = findStrIndex(subject, buffer, dataLocation);
	int strIndex = findStrIndex("\"", buffer, keyIndex);

	std::string str = getBytes(strIndex, size, buffer);
	this->_dataLocation = strIndex + size;
	return str;
}


std::string getBytes(int skipTo, int dataSize, std::vector<char> buffer)
{
	std::string ret;
	for (size_t i = skipTo; i < dataSize + skipTo; i++)
	{
		ret.push_back(buffer[i]);
	}
	return ret;
}


size_t findStrIndex(std::string str, std::vector<char> buffer, int skipTo)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);//make the str lowercase -> not case sensetive
	std::string bufferStr(buffer.begin(), buffer.end());//crate string from vector
	bufferStr = bufferStr.substr(skipTo - 1, bufferStr.size());//cut all until startPoint
	size_t index = bufferStr.find(str);
	if (index == std::string::npos)//string not found
	{
		return -1;
	}
	return index + skipTo; //return index of str in buffer
}