#include "Server.h"

Server::Server(IDataBase * db)
{
	_m_database = db;
	_m_handlerFactory = new RequestHandlerFactory(_m_database);
	_m_communicator = new Communicator(_m_database);
}

Server::~Server()
{
	delete(_m_handlerFactory);
	_m_handlerFactory = nullptr;
}

void Server::run()
{

}