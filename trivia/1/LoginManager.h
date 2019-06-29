#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <mutex>
#include <string>
#include "IDatabase.h"
#include "LoggedUser.h"
#include <WinSock2.h>
#include <Windows.h>


class LoginManager
{
public:
	LoginManager(IDataBase * dataBase, vector<LoggedUser> loggedUsers);
	~LoginManager();
	int signup(std::string username, std::string password, std::string email,SOCKET socket);
	int login(std::string username, std::string password,SOCKET socket);
	int logout(std::string username);


private:
	IDataBase * _m_dataBase;
	std::vector<LoggedUser> _m_loggedUsers;
};


