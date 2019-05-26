#pragma once

#include <algorithm>
#include <vector>
#include "LoginRequest.h"
#include "SignupRequest.h"

struct JsonRequestPacketDeserializer
{
	 LoginRequest deserializeLoginRequest(std::vector<char> buffer);
     SignupRequest deserializeSignupRequest(std::vector<char> buffer);
private:
	std::string analyzeJson(std::vector<char> buffer, std::string subject, int dataLocation, int sizeLocation, int sizeLength);
	int _dataLocation;
};

std::string getBytes(int skipTo, int dataSize, std::vector<char> buffer);

size_t findStrIndex(std::string str, std::vector<char> buffer, int startPoint);
