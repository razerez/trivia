#pragma once

#include <iostream>

class LoggedUser
{
public:
	LoggedUser(std::string _m_username);
	~LoggedUser();
	std::string getUsername();

private:
	std::string _m_username;
};