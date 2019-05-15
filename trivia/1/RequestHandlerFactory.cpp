#pragma once
#include "RequestHandlerFactory.h"

LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler * nb = new LoginRequestHandler(this->_m_loginManager, this);
	return *nb;
}

RequestHandlerFactory::RequestHandlerFactory(IDataBase * l)
{

	vector<LoggedUser> mb;
	_m_loginManager = new LoginManager(l, mb);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete(_m_loginManager);
}