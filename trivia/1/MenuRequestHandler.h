#pragma once


#include "LoggedUser.h"
#include "RoomManager.h"
#include "HighscoreTable.h"
#include "RequestHandlerFactory.h"
#include "Request.h"
#include "RequestResult.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "MyStatusReport.h"


class RequestHandlerFactory;


class MenuRequestHandler : public IRequestHandler
{
	LoggedUser _m_username;
	RoomManager * _m_roomManager;
	MyStatusReport *_m_myStatus;
	HighscoreTable * _m_highscoreTable;
	RequestHandlerFactory * _m_handlerFactory;
	//private functions
	RequestResult signOut(Request req, SOCKET socket);
	RequestResult getRooms(Request req);
	RequestResult getPlayersInRoom(Request req);
	RequestResult getHighscores(Request req);
	RequestResult joinRoom(Request req);
	RequestResult createRoom(Request req);
	RequestResult myStatus(Request req);


public:
	MenuRequestHandler(LoggedUser* username, RoomManager * m_roomManager, HighscoreTable * m_highScoreTable, RequestHandlerFactory * m_handlerFactory, MyStatusReport* myStatus);
	~MenuRequestHandler();
	LoggedUser getUsername();
	void setUsername(LoggedUser username);
	virtual bool isRequestRelevant(Request req);
	virtual RequestResult handleRequest(Request req, SOCKET socket);


};