#pragma once
#include "RequestHandlerFactory.h"

LoginRequestHandler * RequestHandlerFactory::createLoginRequestHandler(LoggedUser l)
{
	LoginRequestHandler * nb = new LoginRequestHandler(this->_m_loginManager, this, l);
	return nb;
}


LoginRequestHandler * RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler * nb = new LoginRequestHandler(this->_m_loginManager, this);
	return nb;
}


MenuRequestHandler * RequestHandlerFactory::createMenuRequestHandler(LoggedUser l)
{
	MenuRequestHandler * nb = new MenuRequestHandler(&l, this->_m_roomManager, this->_m_highscoreTable, this);
	return nb;
}




RequestHandlerFactory::RequestHandlerFactory(IDataBase * l)
{
	loggedUsers = new std::vector<LoggedUser>;
	_m_loginManager = new LoginManager(l, *loggedUsers);
	_m_roomManager = new RoomManager();
	_m_highscoreTable = new HighscoreTable(l);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	if(_m_loginManager!=nullptr)delete(_m_loginManager);
	if (loggedUsers != nullptr)delete(loggedUsers);
	if (_m_highscoreTable != nullptr)delete(_m_highscoreTable);
	if (_m_roomManager != nullptr)delete(_m_roomManager);
}
