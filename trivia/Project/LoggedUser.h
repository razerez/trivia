#pragma once

#include <iostream>

class LoggedUser
{
public:
	LoggedUser();
	~LoggedUser();
	std::string getUsername();

private:
	std::string _m_username;
};