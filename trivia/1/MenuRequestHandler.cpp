#include "MenuRequestHandler.h"




RequestResult MenuRequestHandler::signOut(Request req)
{
	RequestResult result = this->_m_handlerFactory->createLoginRequestHandler()->handleRequest(req);
	result._newHandler = this->_m_handlerFactory->createLoginRequestHandler(); // need to change
	return result;
}

RequestResult MenuRequestHandler::getRooms(Request req)
{
	//no desirelize
	std::vector<char> buff;
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::getPlayersInRoom(Request req)
{
	GetPlayersInRoomRequest user = JsonRequestPacketDeserializer().deserializeGetPlayersRequest(req._buffer);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse(this->_m_roomManager->getPlayersInRooms(user.roomId)));
	IRequestHandler* nextHandler = this;
	return RequestResult(buff, nextHandler);

}

RequestResult MenuRequestHandler::getHighscores(Request req)
{
	//no desirelize
	std::vector<char> buff;
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::joinRoom(Request req)
{
	JoinRoomRequest user = JsonRequestPacketDeserializer().deserializeJoinRoomRequest(req._buffer);
	int stat = this->_m_roomManager->joinRoom(*this->_m_user, user.roomId);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse(stat));
	IRequestHandler* nextHandler = this;
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::createRoom(Request req)
{
	CreateRoomRequest user = JsonRequestPacketDeserializer().deserializeCreateRoomRequest(req._buffer);
	RoomData roomData(0, user.roomName, user.maxUsers, user.answerTimeout, 1);
	int stat = this->_m_roomManager->createRoom(*this->_m_user, roomData);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse(stat));
	IRequestHandler* nextHandler = this;
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

