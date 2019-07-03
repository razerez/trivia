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
	LoginRequestHandler(LoginManager* m_loginManager, RequestHandlerFactory* m_handlerFactory,LoggedUser username);
	~LoginRequestHandler();
	bool isRequestRelevant(Request req);
	RequestResult handleRequest(Request req,SOCKET socket);
	LoggedUser getUsername();
	virtual void setUsername(LoggedUser user);
private:
	LoggedUser _m_username;
	LoginManager* _m_loginManager;
	RequestHandlerFactory* _m_handlerFactory;
	RequestResult exit(Request req);
	RequestResult login(Request req, SOCKET socket);
	RequestResult signup(Request req, SOCKET socket);
	RequestResult logout(Request req, SOCKET socket);
};
