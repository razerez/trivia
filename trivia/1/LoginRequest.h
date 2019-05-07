#pragma once
#include <iostream>
struct LoginRequest
{
	std::string _username;
	std::string _password;
public:
	LoginRequest(std::string, std::string);
	~LoginRequest();

};