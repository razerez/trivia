#pragma once
#include "IRequestHandler.h"
#include "RequestResult.h"

class LoginRequestHandler:IRequestHandler
{
public:
	LoginRequestHandler();
	~LoginRequestHandler();
	bool isRequestRelevant(Request req);
	RequestResult handleRequest(Request req);
	RequestResult login(Request req);
	RequestResult signup(Request req);
private:

};