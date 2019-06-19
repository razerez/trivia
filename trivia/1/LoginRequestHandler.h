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
	~LoginRequestHandler();
	bool isRequestRelevant(Request req);
	RequestResult handleRequest(Request req);

private:
	LoginManager* _m_loginManager;
	RequestHandlerFactory* _m_handlerFactory;
	RequestResult exit(Request req);
	RequestResult login(Request req);
	RequestResult signup(Request req);
	RequestResult logout(Request req);
};
