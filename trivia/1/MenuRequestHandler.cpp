#include "MenuRequestHandler.h"



//finish
RequestResult MenuRequestHandler::signOut(Request req)
{
	RequestResult result = this->_m_handlerFactory->createLoginRequestHandler(_m_username)->handleRequest(req);
	result._newHandler = this->_m_handlerFactory->createLoginRequestHandler(); // need to change
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

//not finish need to check
RequestResult MenuRequestHandler::getHighscores(Request req)
{
	HighscoreResponse newHigh(1, *this->_m_highscoreTable);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(HighscoreResponse(1, *this->_m_highscoreTable));
	IRequestHandler * nextHandler = this;
	return RequestResult(buff, nextHandler);
}

//finish
RequestResult MenuRequestHandler::joinRoom(Request req)
{
	JoinRoomRequest user = JsonRequestPacketDeserializer().deserializeJoinRoomRequest(req._buffer);
	int stat = this->_m_roomManager->joinRoom(this->_m_username, user.roomId);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse(stat));

	Room * newRoom = new Room(this->_m_roomManager->getRoom(user.roomId).getRoomData(), this->_m_roomManager->getRoom(user.roomId).getAllUsers());
	
	IRequestHandler* nextHandler = this->_m_handlerFactory->createRoomMemberRequestHandler(this->_m_username, newRoom);
	return RequestResult(buff, nextHandler);
}

//finish
RequestResult MenuRequestHandler::createRoom(Request req)
{
	CreateRoomRequest user = JsonRequestPacketDeserializer().deserializeCreateRoomRequest(req._buffer);
	RoomData roomData(0, user.roomName, user.maxUsers, user.answerTimeout, 1, user.questionCount);
	int stat = this->_m_roomManager->createRoom(this->_m_username, roomData);
	

	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse(stat));

	std::vector<LoggedUser> d;
	d.push_back(this->_m_username);

	Room * newRoom = new Room(roomData, d);

	IRequestHandler* nextHandler = this->_m_handlerFactory->createRoomAdminRequesHandler(this->_m_username, newRoom);
	return RequestResult(buff, nextHandler);
}

RequestResult MenuRequestHandler::myStatus(Request req)
{
	MyStatusResponse ms = (*this->_m_myStatus).getReport(this->_m_username);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(ms);
	for (std::vector<char>::iterator i = buff.begin(); i != buff.end(); ++i)
		std::cout << *i;

	IRequestHandler* nextHandler = this;
	return RequestResult(buff, nextHandler);
}

//finish
MenuRequestHandler::MenuRequestHandler(LoggedUser * username, RoomManager * m_roomManager, HighscoreTable * m_highScoreTable, RequestHandlerFactory * m_handlerFactory, MyStatusReport* myStatus):_m_username(*username)
{
	this->_m_myStatus = myStatus;
	this->_m_handlerFactory = m_handlerFactory;
	this->_m_roomManager = m_roomManager;
	this->_m_highscoreTable = m_highScoreTable;
}

//finish
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
RequestResult MenuRequestHandler::handleRequest(Request req)
{
	char reqId = req._buffer[0];
	if (reqId == 'O')
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
	else if (reqId == 'M')
	{
		return myStatus(req);
	}
}

