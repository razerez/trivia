#pragma once
#include "Request.h"
#include "RequestResult.h"
#include "LoggedUser.h"
#include <ctime>
#include <vector>
#include <string>
using std::string;
struct RequestResult;
struct IRequestHandler
{
private:
	LoggedUser _m_username;
public:
	IRequestHandler();
	IRequestHandler(LoggedUser username);
	~IRequestHandler();
	virtual LoggedUser getUsername()=0;
	virtual void setUsername(LoggedUser username)=0;
	virtual bool isRequestRelevant(Request req) = 0;
	virtual RequestResult handleRequest(Request req) = 0;
};
