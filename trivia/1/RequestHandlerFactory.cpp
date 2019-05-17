#pragma once
#include "RequestHandlerFactory.h"

LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler * nb = new LoginRequestHandler(this->_m_loginManager, this);
	return *nb;
}

RequestHandlerFactory::RequestHandlerFactory(IDataBase * l, vector<LoggedUser> v)
{
	_m_loginManager = new LoginManager(l, v);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete(_m_loginManager);
}
