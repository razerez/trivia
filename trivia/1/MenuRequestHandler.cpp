#include "MenuRequestHandler.h"

/*
step 1) deserialize
step 2) the action
step 3) serialize
step 4) nextHandler
*/

//finish
RequestResult MenuRequestHandler::signOut(Request req, SOCKET socket)
{
	RequestResult result = this->_m_handlerFactory->createLoginRequestHandler(_m_username)->handleRequest(req, socket);
	result._newHandler = this->_m_handlerFactory->createLoginRequestHandler(LoggedUser("",socket)); // need to change
	return result;
}

//finish
RequestResult MenuRequestHandler::getRooms(Request req)
{

	GetRoomsResponse myRoom(this->_m_roomManager->getRooms(), 1);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(myRoom);
	IRequestHandler* nextHandler = this;
	return RequestResult(buff, nextHandler);
}

//finish
RequestResult MenuRequestHandler::getPlayersInRoom(Request req)
{
	GetPlayersInRoomRequest user = JsonRequestPacketDeserializer().deserializeGetPlayersRequest(req._buffer);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse(this->_m_roomManager->getPlayersInRooms(user.roomId)));
	IRequestHandler* nextHandler = this;
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::getHighscores(Request req)
{
	HighscoreResponse newHigh(1, *this->_m_highscoreTable);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(HighscoreResponse(1, *this->_m_highscoreTable));
	IRequestHandler * nextHandler = this;
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::joinRoom(Request req)
{
	JoinRoomRequest user = JsonRequestPacketDeserializer().deserializeJoinRoomRequest(req._buffer);
	int stat = this->_m_roomManager->joinRoom(this->_m_username, user.roomId);

	vector<SOCKET> v;
	vector<string> namesVec;
	vector<LoggedUser> loggedUserVec = this->_m_roomManager->getRoom(user.roomId)->getAllUsers();

	for (vector<LoggedUser>::iterator it = loggedUserVec.begin(); it != loggedUserVec.end(); ++it)
	{
		namesVec.push_back((*it).getUsername());
		v.push_back((*it).getSocket());
	}

	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse(namesVec));

	Room * newRoom = this->_m_roomManager->getRoom(user.roomId);

	IRequestHandler* nextHandler = this->_m_handlerFactory->createRoomMemberRequestHandler(this->_m_username, newRoom);

	return RequestResult(buff, nextHandler, v);
}

//finish
RequestResult MenuRequestHandler::createRoom(Request req)
{
	CreateRoomRequest user = JsonRequestPacketDeserializer().deserializeCreateRoomRequest(req._buffer);
	RoomData roomData(0, user.roomName, user.maxUsers, user.answerTimeout, 0, user.questionCount);
	int stat = this->_m_roomManager->createRoom(this->_m_username, roomData);
	

	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse(stat));

	Room * newRoom = this->_m_roomManager->getRoom(roomData._id);


	IRequestHandler* nextHandler = this->_m_handlerFactory->createRoomAdminRequesHandler(this->_m_username, newRoom);
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::myStatus(Request req)
{
	MyStatusResponse ms = (*this->_m_myStatus).getReport(this->_m_username);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(ms);

	IRequestHandler* nextHandler = this;
	return RequestResult(buff, nextHandler);
}


MenuRequestHandler::MenuRequestHandler(LoggedUser * username, RoomManager * m_roomManager, HighscoreTable * m_highScoreTable, RequestHandlerFactory * m_handlerFactory, MyStatusReport* myStatus):_m_username(*username)
{
	this->_m_myStatus = myStatus;
	this->_m_handlerFactory = m_handlerFactory;
	this->_m_roomManager = m_roomManager;
	this->_m_highscoreTable = m_highScoreTable;
}


MenuRequestHandler::~MenuRequestHandler()
{
}

LoggedUser MenuRequestHandler::getUsername()
{
	return _m_username;
}

void MenuRequestHandler::setUsername(LoggedUser username)
{
	_m_username = username;
}

//finish
bool MenuRequestHandler::isRequestRelevant(Request req)
{
	
	char reqId = req._buffer[0];
	if (reqId == 'O'|| reqId == 'G' || reqId == 'P' || reqId == 'H'|| reqId == 'J' || reqId == 'C' || reqId == 'M')
	{
		return true;
	}
	return false;
}

//finish
RequestResult MenuRequestHandler::handleRequest(Request req, SOCKET socket)
{
	char reqId = req._buffer[0];
	if (reqId == 'O')
	{
		return signOut(req, socket);
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
	else if (reqId == 'M')
	{
		return myStatus(req);
	}
}

