#pragma once
#include <iostream>
#include <string>

struct LoginRequest
{
	LoginRequest(std::string, std::string);
	~LoginRequest();

	std::string _username;
	std::string _password;
};