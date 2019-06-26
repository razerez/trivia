#pragma once

#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "Request.h"
#include "RequestResult.h"


class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
	LoggedUser _m_loggedUser;
	Room * _m_room;
	RoomManager * _m_roomManager;
	RequestHandlerFactory * _m_handlerFactory;

	RequestResult leaveRoom(Request request);
	RequestResult GetRoomState(Request request);

public:
	RoomMemberRequestHandler(Room * _m_room, LoggedUser * _m_loggedUser, RoomManager * _m_roomManager, RequestHandlerFactory * _m_handlerFactory);
	~RoomMemberRequestHandler();

	virtual LoggedUser getUsername();
	virtual void setUsername(LoggedUser username);
	virtual bool isRequestRelevant(Request request);
	virtual RequestResult handleRequest(Request request);


};