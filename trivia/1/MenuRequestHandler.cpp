#include "MenuRequestHandler.h"




RequestResult MenuRequestHandler::signOut(Request req)
{
	
	RequestResult result = this->_m_handlerFactory->createLoginRequestHandler()->handleRequest(req);
	result._newHandler = nullptr; // need to change
	return result;
}

RequestResult MenuRequestHandler::getRooms(Request req)
{

	std::vector<char> buff;
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::getPlayersInRoom(Request req)
{
	//GetPlayersInRoomRequest rooms = JsonRequestPacketDeserializer().deserializeGetPlayersRequest(req._buffer);
	//int stat = this->
	//std::vector<char> buff = JsonResponsePacketSerializer(GetPlayersInRoomResponse(stat));

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
	CreateRoomRequest user = JsonRequestPacketDeserializer().deserializeCreateRoomRequest(req._buffer);
	//int stat = this->_m_roomManager->createRoom()

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
	
	char reqId = req._buffer[0];
	if (reqId == 'S' || reqId == 'G' || reqId == 'P' || reqId == 'H'|| reqId == 'J' || reqId == 'C')
	{
		return true;
	}
	return false;
}

RequestResult MenuRequestHandler::handleRequest(Request req)
{
	char reqId = req._buffer[0];
	if (reqId == 'S')
	{
		return signOut(req);
	}
	else if (reqId == 'G')
	{
		return getRooms(req);
	}
	else if (reqId == 'P')
	{
		return getPlayersInRoom(req);
	}
	else if (reqId == 'H')
	{
		return getHighscores(req);
	}
	else if (reqId == 'J')
	{
		return joinRoom(req);
	}
	else if (reqId == 'C')
	{
		return createRoom(req);
	}
}

