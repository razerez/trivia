#pragma once

#include <iostream>

struct SignupRequest
{
	std::string _username;
	std::string _password;
	std::string _email;
public:
	SignupRequest(std::string, std::string, std::string);
	~SignupRequest();
};