#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequest.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "HighscoreTable.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "MyStatusReport.h"
#include "MyStatusResponse.h"
#include <vector>

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class RequestHandlerFactory
{
private:
	LoginManager * _m_loginManager;
	std::vector<LoggedUser> * loggedUsers;
	RoomManager * _m_roomManager;
	HighscoreTable * _m_highscoreTable;
	MyStatusReport * _m_myStatus;
public:
	LoginRequestHandler * createLoginRequestHandler(LoggedUser l);
	LoginRequestHandler * createLoginRequestHandler();
	MenuRequestHandler * createMenuRequestHandler(LoggedUser l);
	RoomAdminRequestHandler * createRoomAdminRequesHandler(LoggedUser l, Room * r);
	RoomMemberRequestHandler * createRoomMemberRequestHandler(LoggedUser l, Room * r);
	
	RequestHandlerFactory(IDataBase* l);
	~RequestHandlerFactory();



};