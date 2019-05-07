#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequest.h"
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
private:
	LoginManager * _m_loginManager;

public:
	LoginRequestHandler createLoginRequestHandler();
	RequestHandlerFactory(IDataBase* l);
	~RequestHandlerFactory();



};

LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
	return LoginRequestHandler();
}

RequestHandlerFactory::RequestHandlerFactory(IDataBase * l)
{
	_m_loginManager = new LoginManager(l);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete(_m_loginManager);
}