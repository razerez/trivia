#pragma once

#include "LoggedUser.h"
#include "RoomManager.h"
#include "HighscoreTable.h"
#include "RequestHandlerFactory.h"
#include "Request.h"
#include "RequestResult.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"



class RequestHandlerFactory;


class MenuRequestHandler : public IRequestHandler
{
	LoggedUser * _m_user;
	RoomManager * _m_roomManager;
	HighscoreTable * _m_highscoreTable;
	RequestHandlerFactory * _m_handlerFactory;

	//private functions
	RequestResult signOut(Request req);
	RequestResult getRooms(Request req);
	RequestResult getPlayersInRoom(Request req);
	RequestResult getHighscores(Request req);
	RequestResult joinRoom(Request req);
	RequestResult createRoom(Request req);



public:
	MenuRequestHandler(LoggedUser * m_user, RoomManager * m_roomManager, HighscoreTable * m_highScoreTable, RequestHandlerFactory * m_handlerFactory);
	~MenuRequestHandler();

	bool isRequestRelevant(Request req);
	RequestResult handlerRequest(Request req);



};