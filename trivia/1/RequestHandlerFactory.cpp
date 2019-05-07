#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequest.h"
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
private:
	LoginManager* _m_loginManager;

public:
	LoginRequestHandler createLoginRequestHandler();
	RequestHandlerFactory(IDataBase* l);
	~RequestHandlerFactory();



};
