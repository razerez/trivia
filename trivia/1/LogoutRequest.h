#pragma once
#pragma once
#include <iostream>
#include <string>

struct LogoutRequest
{
	LogoutRequest(std::string username);
	~LogoutRequest();

	std::string _username;
};