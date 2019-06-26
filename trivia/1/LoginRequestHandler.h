#pragma once
#include <iostream>
#include <string>
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "IRequestHandler.h"
#include "RequestResult.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"


class RequestHandlerFactory;

class LoginRequestHandler: public IRequestHandler
{
public:
	LoginRequestHandler(LoginManager* m_loginManager, RequestHandlerFactory* m_handlerFactory);
	LoginRequestHandler(LoginManager* m_loginManager, RequestHandlerFactory* m_handlerFactory,LoggedUser username);
	~LoginRequestHandler();
	bool isRequestRelevant(Request req);
	RequestResult handleRequest(Request req);
	LoggedUser getUsername();
	void setUsername(LoggedUser username);
private:
	LoggedUser _m_username;
	LoginManager* _m_loginManager;
	RequestHandlerFactory* _m_handlerFactory;
	RequestResult exit(Request req);
	RequestResult login(Request req);
	RequestResult signup(Request req);
	RequestResult logout(Request req);
};
