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
#include "GameRequestHandler.h"
#include "MyStatusReport.h"
#include "MyStatusResponse.h"
#include "Game.h"
#include "GameManager.h"

#include <vector>

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;
class RequestHandlerFactory
{
private:
	LoginManager * _m_loginManager;
	std::vector<LoggedUser> * loggedUsers;
	RoomManager * _m_roomManager;
	HighscoreTable * _m_highscoreTable;
	MyStatusReport * _m_myStatus;
	GameManager * _m_gameManager;


public:
	LoginRequestHandler * createLoginRequestHandler(LoggedUser l);
	MenuRequestHandler * createMenuRequestHandler(LoggedUser l);
	RoomAdminRequestHandler * createRoomAdminRequesHandler(LoggedUser l, Room * r);
	RoomMemberRequestHandler * createRoomMemberRequestHandler(LoggedUser l, Room * r);
	GameRequestHandler* createGameRequestHandler(LoggedUser * l, Room * r);

	RequestHandlerFactory(IDataBase* l);
	~RequestHandlerFactory();



};