#include "RequestHandlerFactory.h"


LoginRequestHandler * RequestHandlerFactory::createLoginRequestHandler(LoggedUser l)
{
	LoginRequestHandler * nb = new LoginRequestHandler(this->_m_loginManager, this, l);
	return nb;
}


MenuRequestHandler * RequestHandlerFactory::createMenuRequestHandler(LoggedUser l)
{
	MenuRequestHandler * nb = new MenuRequestHandler(&l, this->_m_roomManager, this->_m_highscoreTable, this,this->_m_myStatus);
	return nb;
}

RoomAdminRequestHandler * RequestHandlerFactory::createRoomAdminRequesHandler(LoggedUser l, Room * r)
{
	RoomAdminRequestHandler * nb = new RoomAdminRequestHandler(r, &l, this->_m_roomManager, this);
	return nb;
}

RoomMemberRequestHandler * RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser l, Room * r)
{
	RoomMemberRequestHandler * nb = new RoomMemberRequestHandler(r, &l, this->_m_roomManager, this);
	return nb;
}

GameRequestHandler * RequestHandlerFactory::createGameRequestHandler(LoggedUser * l, Room * r)
{
	GameRequestHandler * nb = new GameRequestHandler(l, this, this->_m_gameManager->CreateGame(*r), this->_m_gameManager);
	return nb;
}





RequestHandlerFactory::RequestHandlerFactory(IDataBase * l)
{
	loggedUsers = new std::vector<LoggedUser>;
	_m_loginManager = new LoginManager(l, *loggedUsers);
	_m_roomManager = new RoomManager();
	_m_highscoreTable = new HighscoreTable(l);
	_m_myStatus = new MyStatusReport(l);
	_m_gameManager = new GameManager(l, vector<Game>());


}

RequestHandlerFactory::~RequestHandlerFactory()
{
	if(_m_loginManager!=nullptr)delete(_m_loginManager);
	_m_loginManager = nullptr;
	if (_m_myStatus != nullptr)delete(_m_myStatus);
	_m_myStatus = nullptr;
	if (loggedUsers != nullptr)delete(loggedUsers);
	loggedUsers = nullptr;
	if (_m_highscoreTable != nullptr)delete(_m_highscoreTable);
	_m_highscoreTable = nullptr;
	if (_m_roomManager != nullptr)delete(_m_roomManager);
	_m_roomManager = nullptr;
	if (_m_gameManager != nullptr)delete(_m_gameManager);
	_m_gameManager = nullptr;
}
