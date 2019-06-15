#pragma once
#include "RequestHandlerFactory.h"

LoginRequestHandler * RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler * nb = new LoginRequestHandler(this->_m_loginManager, this);
	return nb;
}

MenuRequestHandler * RequestHandlerFactory::createMenuRequestHandler()
{
	std::vector<LoggedUser>::iterator it;
	MenuRequestHandler * nb = new MenuRequestHandler(&(it[0]), this->_m_roomManager, this->_m_highscoreTable, this);
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
	delete(_m_loginManager);
	delete(loggedUsers);
}
