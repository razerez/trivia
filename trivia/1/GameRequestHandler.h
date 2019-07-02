#pragma once
#include <iostream>
#include <string>
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoggedUser.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Game.h"
#include "GameManager.h"


class RequestHandlerFactory;

class GameRequestHandler: public IRequestHandler
{
private:
	LoggedUser _m_username;
	RequestHandlerFactory * _m_HandlerFactory;
	Game * _m_game;
	GameManager * _m_gameManager;

	RequestResult getQuestion(Request req);
	RequestResult submitAnswer(Request req);
	RequestResult getGameResult(Request req);
	RequestResult leaveGame(Request req);

public:
	GameRequestHandler(LoggedUser* username, RequestHandlerFactory * m_handlerFactory, Game * m_game, GameManager * m_gameManager);
	~GameRequestHandler();
	
	virtual LoggedUser getUsername();
	virtual void setUsername(LoggedUser username);

	virtual bool isRequestRelevant(Request req);
	virtual RequestResult handleRequest(Request request, SOCKET socket);




};