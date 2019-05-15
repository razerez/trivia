#pragma once

#include <iostream>
#include <vector>

#include "IDatabase.h"
#include "LoggedUser.h"



class LoginManager
{
public:
	LoginManager(IDataBase * dataBase, vector<LoggedUser> loggedUsers);
	~LoginManager();
	void signup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout();


private:
	IDataBase * _m_dataBase;
	std::vector<LoggedUser> _m_loggedUsers;
};

