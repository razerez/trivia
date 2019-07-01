#pragma once

#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
class LoggedUser
{
public:
	LoggedUser(std::string ,SOCKET);
	~LoggedUser();
	std::string getUsername();
	SOCKET getSocket();
private:
	std::string _m_username;
	SOCKET _m_socket;
};