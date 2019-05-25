#include "JsonRequestPacketDeserializer.h"

#define CODE_SEGMENT 1
#define DATA_SIZE_SEGMENT 4
#define USERNAME_SIZE_SEGMENT 1
#define PASSWORD_SIZE_SEGMENT 1
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char> buffer)
{
	int usernameSize = stoi(getBytes(CODE_SEGMENT, USERNAME_SIZE_SEGMENT, buffer));
	int passwordSize = stoi(getBytes(CODE_SEGMENT + USERNAME_SIZE_SEGMENT, PASSWORD_SIZE_SEGMENT, buffer));

	LoginRequest myLogin("swe", "wewe");
	return myLogin;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<char> buffer)
{
	SignupRequest mySignup("wef", "ewe", "we");
	return mySignup;
}


std::string getBytes(int startPoint, int amount, std::vector<char> buffer)
{
	std::string ret;
	for (size_t i = startPoint; i < amount; i++)
	{
		ret.push_back(buffer[i]);
	}
	return ret;
}

//int findStrIndex(std::string str, std::vector<char> buffer)
//{
//	str.find()
//	int index = 0;
//	bool stayJ = true;//flag
//	bool stayI = true;//flag
//	bool strFound = true;
//	for (size_t i = 0; i < buffer.size(); i++)
//	{
//		if (CODE_SEGMENT + DATA_SIZE_SEGMENT + i + str.size() > buffer.size() - (CODE_SEGMENT + DATA_SIZE_SEGMENT + i))
//		{
//			stayI = false;
//			stayJ = false;
//		}
//		for (size_t j = 0; j < str.size() && stayJ; j++)
//		{
//			if (!buffer[CODE_SEGMENT + DATA_SIZE_SEGMENT + i + j] == str[j])
//			{
//				strFound = false;//str not found
//				stayJ = false;//exit loop
//			}
//		}
//		if (strFound)
//		{
//			index = CODE_SEGMENT + DATA_SIZE_SEGMENT + i;
//			return index;
//		}
//		stayJ = true;
//
//	}
//}

int findStrIndex(std::string str, std::vector<char> buffer)
{
	std::string bufferStr(buffer.begin(), buffer.end());
	bufferStr.find(str, str.size());
}