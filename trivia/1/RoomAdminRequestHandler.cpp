#include "RoomAdminRequestHandler.h"

RequestResult RoomAdminRequestHandler::closeRoom(Request request)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::StartGame(Request request)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::GetRoomState(Request request)
{
	return RequestResult();
}

RoomAdminRequestHandler::RoomAdminRequestHandler(Room * _m_room, LoggedUser * _m_loggedUser, RoomManager * _m_roomManager, RequestHandlerFactory * _m_handlerFactory):_m_loggedUser(_m_loggedUser)
{
	this->_m_room = _m_room;
	this->_m_handlerFactory = _m_handlerFactory;
	this->_m_roomManager = _m_roomManager;
}

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
}

bool RoomAdminRequestHandler::isRequestRelevant(Request request)
{
	

	char reqId = request._buffer[0];
	if (reqId == 'D' || reqId == 'S' || reqId == 'R' || reqId == 'L')
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
	else if (reqId == 'L')
	{
		return;
	}
}
