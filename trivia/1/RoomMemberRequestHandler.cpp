#include "RoomMemberRequestHandler.h"

RequestResult RoomMemberRequestHandler::leaveRoom(Request request)
{
	this->_m_room->deleteUser(this->_m_loggedUser);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse(1));
	IRequestHandler* nextHandler = this->_m_handlerFactory->createMenuRequestHandler(this->_m_loggedUser);
	return RequestResult(buff, nextHandler);
	
}

RequestResult RoomMemberRequestHandler::GetRoomState(Request request)
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

RoomMemberRequestHandler::RoomMemberRequestHandler(Room * _m_room, LoggedUser * _m_loggedUser, RoomManager * _m_roomManager, RequestHandlerFactory * _m_handlerFactory) :_m_loggedUser(*_m_loggedUser)
{
	this->_m_room = _m_room;
	this->_m_handlerFactory = _m_handlerFactory;
	this->_m_roomManager = _m_roomManager;
}

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
}

LoggedUser RoomMemberRequestHandler::getUsername()
{
	return this->_m_loggedUser;
}

void RoomMemberRequestHandler::setUsername(LoggedUser username)
{
	this->_m_loggedUser = username;
}

bool RoomMemberRequestHandler::isRequestRelevant(Request request)
{
	char reqId = request._buffer[0];
	if (reqId == 'L'|| reqId == 'R')
	{
		return true;
	}
	return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(Request request, SOCKET socket)
{
	char reqId = request._buffer[0];
	if (reqId == 'L')
	{
		return leaveRoom(request);
	}
	else if (reqId == 'R')
	{
		return GetRoomState(request);
	}
}
