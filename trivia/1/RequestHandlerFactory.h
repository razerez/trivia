#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequest.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include"HighscoreTable.h"
//#include "MenuRequestHandler"

#include <vector>

class LoginRequestHandler;

class RequestHandlerFactory
{
private:
	LoginManager * _m_loginManager;
	std::vector<LoggedUser> * loggedUsers;
	RoomManager _m_roomManager;
	//HighscoreTable _m_highscoreTable;

public:
	LoginRequestHandler * createLoginRequestHandler();
	//MenuRequestHandler createMenuRequestHandler();

	
	RequestHandlerFactory(IDataBase* l);
	~RequestHandlerFactory();



};