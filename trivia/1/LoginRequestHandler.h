#pragma once
#include <iostream>
#include <string>
#include "LoginRequest.h"
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
	LoginRequestHandler(LoginManager* m_loginManager, RequestHandlerFactory* m_handlerFacroty);
	~LoginRequestHandler();
	bool isRequestRelevant(Request req);
	RequestResult handleRequest(Request req);

private:
	LoginManager* _m_loginManager;
	RequestHandlerFactory* _m_handlerFacroty;
	RequestResult login(Request req);
	RequestResult signup(Request req);
};

string getBytes(int startPoint, int amount, std::vector<char> buffer);
