#pragma once

#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "Request.h"
#include "RequestResult.h"


class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
	LoggedUser _m_username;
	Room * _m_room;
	RoomManager * _m_roomManager;
	RequestHandlerFactory * _m_handlerFactory;

	RequestResult closeRoom(Request request);
	RequestResult StartGame(Request request);
	RequestResult GetRoomState(Request request);

public:
	RoomAdminRequestHandler(Room * _m_room, LoggedUser * _m_loggedUser, RoomManager * _m_roomManager, RequestHandlerFactory * _m_handlerFactory);
	~RoomAdminRequestHandler();

	virtual LoggedUser getUsername();
	virtual void setUsername(LoggedUser username);
	virtual bool isRequestRelevant(Request request);
	virtual RequestResult handleRequest(Request request, SOCKET socket);

};
