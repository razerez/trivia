#include "JsonRequestPacketDeserializer.h"

#define CODE_SEGMENT 1
#define DATA_SIZE_SEGMENT 4
#define USERNAME_SIZE_SEGMENT 1
#define PASSWORD_SIZE_SEGMENT 1

#define EMAIL_SIZE_SEGMENT 1
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char> buffer)
{
	int usernameSize = stoi(getBytes(CODE_SEGMENT, USERNAME_SIZE_SEGMENT, buffer));
	int usernameKeyIndex = findStrIndex("username:", buffer, DATA_SIZE_SEGMENT);
	int usernameIndex = findStrIndex("\"", buffer, usernameKeyIndex);
	std::string username = getBytes(usernameIndex, usernameSize, buffer);

	int passwordSize = stoi(getBytes(CODE_SEGMENT + USERNAME_SIZE_SEGMENT, PASSWORD_SIZE_SEGMENT, buffer));
	int passwordKeyIndex = findStrIndex("password:", buffer, DATA_SIZE_SEGMENT);
	int passwordIndex = findStrIndex("\"", buffer, passwordKeyIndex);
	std::string password = getBytes(passwordIndex, passwordSize, buffer);

	LoginRequest myLogin(username, password);
	return myLogin;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<char> buffer)
{
	int emailSize = stoi(getBytes(CODE_SEGMENT + USERNAME_SIZE_SEGMENT + PASSWORD_SIZE_SEGMENT, EMAIL_SIZE_SEGMENT, buffer));
	int emailKeyIndex = findStrIndex("email:", buffer, DATA_SIZE_SEGMENT);
	int emailIndex = findStrIndex("\"", buffer, emailKeyIndex);
	std::string email = getBytes(emailIndex, emailSize, buffer);

	LoginRequest myLogin = deserializeLoginRequest(buffer);
	std::string username = myLogin._username;
	std::string password = myLogin._password;

	SignupRequest mySignup(username, password, email);
	return mySignup;
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
	return bufferStr.find(str, str.size()); //return index of str in buffer// if not found return std::string::npos
}