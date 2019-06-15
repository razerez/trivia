#include "MenuRequestHandler.h"




RequestResult MenuRequestHandler::signOut(Request req)
{
	std::vector<char> buff;
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::getRooms(Request req)
{
	std::vector<char> buff;
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::getPlayersInRoom(Request req)
{
	std::vector<char> buff;
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::getHighscores(Request req)
{
	std::vector<char> buff;
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::joinRoom(Request req)
{
	std::vector<char> buff;
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::createRoom(Request req)
{
	std::vector<char> buff;
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);
}

MenuRequestHandler::MenuRequestHandler(LoggedUser * m_user, RoomManager * m_roomManager, HighscoreTable * m_highScoreTable, RequestHandlerFactory * m_handlerFactory)
{
	this->_m_user = m_user;
	this->_m_handlerFactory = m_handlerFactory;
	this->_m_roomManager = m_roomManager;
	this->_m_highscoreTable = m_highScoreTable;
}

MenuRequestHandler::~MenuRequestHandler()
{
	delete(this->_m_handlerFactory);
	delete(this->_m_highscoreTable);
	delete(this->_m_roomManager);
	delete(this->_m_user);
}

bool MenuRequestHandler::isRequestRelevant(Request req)
{
	/*
	Need to change 	
	*/
	char reqId = req._buffer[0];
	if (reqId == 'I' || reqId == 'U')
	{
		return true;
	}
	return false;
}

RequestResult MenuRequestHandler::handlerRequest(Request req)
{
	/*
	Need to change
	*/
	char reqId = req._buffer[0];
	if (reqId == 'I')
	{
		return signOut(req);
	}
	else
	{
		return getRooms(req);
	}
}

