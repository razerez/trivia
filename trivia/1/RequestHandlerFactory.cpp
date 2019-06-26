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

RoomAdminRequestHandler * RequestHandlerFactory::createRoomAdminRequesHandler(LoggedUser l, Room * r)
{
	RoomAdminRequestHandler * nb = new RoomAdminRequestHandler(r, &l, this->_m_roomManager, this);
	return nb;
}

RoomMemberRequestHandler * RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser l, Room * r)
{
	RoomMemberRequestHandler * nb = new RoomMemberRequestHandler(r, &l, this->_m_roomManager, this);
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
	_m_loginManager = nullptr;
	if (loggedUsers != nullptr)delete(loggedUsers);
	loggedUsers = nullptr;
	if (_m_highscoreTable != nullptr)delete(_m_highscoreTable);
	_m_highscoreTable = nullptr;
	if (_m_roomManager != nullptr)delete(_m_roomManager);
	_m_roomManager = nullptr;
}
