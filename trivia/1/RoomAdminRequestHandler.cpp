
#include "RoomAdminRequestHandler.h"

RequestResult RoomAdminRequestHandler::closeRoom(Request request)
{
	int stat = this->_m_roomManager->deleteRoom(this->_m_room->getRoomData()._id);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse(stat));
	IRequestHandler* nextHandler = this->_m_handlerFactory->createMenuRequestHandler(this->_m_username);
	return RequestResult(buff, nextHandler);
}


RequestResult RoomAdminRequestHandler::StartGame(Request request)
{
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(StartGameResponse(this->_m_room->getRoomData()._isActive));
	IRequestHandler* nextHandler = this;//need to change all function
	return RequestResult(buff, nextHandler);
}

RequestResult RoomAdminRequestHandler::GetRoomState(Request request)
{
	int id = this->_m_room->getRoomData()._id;
	int active = this->_m_room->getRoomData()._isActive;
	
	int countQuestion = this->_m_room->getRoomData()._questionCount;
	int timePerQuestion = this->_m_room->getRoomData()._timePerQuestion;

	std::vector<LoggedUser> path = this->_m_room->getAllUsers();
	std::vector<string> vec;
	
	for (std::vector<LoggedUser>::iterator i = path.begin(); i != path.end(); ++i)
		vec.push_back((*i).getUsername());

	GetRoomStateResponse myStat(id, active, vec, countQuestion, timePerQuestion);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(myStat);
	IRequestHandler* nextHandler = this;
	return RequestResult(buff, nextHandler);
}

RoomAdminRequestHandler::RoomAdminRequestHandler(Room * _m_room, LoggedUser * _m_loggedUser, RoomManager * _m_roomManager, RequestHandlerFactory * _m_handlerFactory) :_m_username(*_m_loggedUser)
{
	this->_m_room = _m_room;
	this->_m_handlerFactory = _m_handlerFactory;
	this->_m_roomManager = _m_roomManager;
}

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
}

LoggedUser RoomAdminRequestHandler::getUsername()
{
	return this->_m_username;
}

void RoomAdminRequestHandler::setUsername(LoggedUser username)
{
	this->_m_username = username;
}


bool RoomAdminRequestHandler::isRequestRelevant(Request request)
{

	this;
	char reqId = request._buffer[0];
	if (reqId == 'D' || reqId == 'S' || reqId == 'R')
	{
		return true;
	}
	return false;

}

RequestResult RoomAdminRequestHandler::handleRequest(Request request)
{
	char reqId = request._buffer[0];
	if (reqId == 'D')
	{
		return closeRoom(request);
	}
	else if (reqId == 'S')
	{
		return StartGame(request);
	}
	else if (reqId == 'R')
	{
		return GetRoomState(request);
	}
}