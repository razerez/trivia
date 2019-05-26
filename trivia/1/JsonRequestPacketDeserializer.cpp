#include "JsonRequestPacketDeserializer.h"

#define CODE_SEGMENT 1
#define DATA_SIZE_SEGMENT 4
#define USERNAME_SIZE_SEGMENT 1
#define PASSWORD_SIZE_SEGMENT 1

#define EMAIL_SIZE_SEGMENT 1
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char> buffer)
{
	std::string username = analyzeJson(buffer, "username:", DATA_SIZE_SEGMENT, CODE_SEGMENT, USERNAME_SIZE_SEGMENT);
	std::string password = analyzeJson(buffer, "password:", this->_dataLocation , CODE_SEGMENT + USERNAME_SIZE_SEGMENT, PASSWORD_SIZE_SEGMENT);
	LoginRequest myLogin(username, password);
	return myLogin;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<char> buffer)
{
	LoginRequest myLogin = deserializeLoginRequest(buffer);
	std::string username = myLogin._username;
	std::string password = myLogin._password;
	std::string email = analyzeJson(buffer, "email:", this->_dataLocation, CODE_SEGMENT + USERNAME_SIZE_SEGMENT + PASSWORD_SIZE_SEGMENT, EMAIL_SIZE_SEGMENT);

	SignupRequest mySignup(username, password, email);
	return mySignup;
}



std::string JsonRequestPacketDeserializer::analyzeJson(std::vector<char> buffer, std::string subject, int dataLocation, int sizeLocation, int sizeLength)
//input: buffer, keyWord to search in json, locationOfTheKeyWord, location of the size of the segment, the length of this size
//returns analyzed string from json and insert next dataLocation into this->_dataLocation
{
	int size = stoi(getBytes(sizeLocation, sizeLength, buffer));
	int keyIndex = findStrIndex(subject, buffer, dataLocation);
	int strIndex = findStrIndex("\"", buffer, keyIndex);

	std::string str = getBytes(strIndex, size, buffer);
	this->_dataLocation = strIndex + size;
	return str;
}


std::string getBytes(int skipTo, int dataSize, std::vector<char> buffer)
{
	std::string ret;
	for (size_t i = skipTo; i < dataSize; i++)
	{
		ret.push_back(buffer[i]);
	}
	return ret;
}


size_t findStrIndex(std::string str, std::vector<char> buffer, int skipTo)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);//make the str lowercase -> not case sensetive
	std::string bufferStr(buffer.begin(), buffer.end());//crate string from vector
	bufferStr.substr(buffer[skipTo], bufferStr.size());//cut all until startPoint
	size_t index = bufferStr.find(str, str.size());
	if (index == std::string::npos)//string not found
	{
		return -1;
	}
	return index + skipTo; //return index of str in buffer
}