#pragma once
#include "IRequestHandler.h"
#include "RequestResult.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"

class LoginRequestHandler:IRequestHandler
{
public:
	LoginRequestHandler(LoginManager* m_loginManager, RequestHandlerFactory* m_handlerFacroty);
	~LoginRequestHandler();
	bool isRequestRelevant(Request req);
	RequestResult handleRequest(Request req);
	RequestResult login(Request req);
	RequestResult signup(Request req);
private:
	LoginManager* _m_loginManager;
	RequestHandlerFactory* _m_handlerFacroty;
};