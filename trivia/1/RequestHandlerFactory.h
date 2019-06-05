#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequest.h"
#include "LoginRequestHandler.h"
#include <vector>

class LoginRequestHandler;

class RequestHandlerFactory
{
private:
	LoginManager * _m_loginManager;
	std::vector<LoggedUser> * loggedUsers;
public:
	LoginRequestHandler * createLoginRequestHandler();
	RequestHandlerFactory(IDataBase* l);
	~RequestHandlerFactory();



};