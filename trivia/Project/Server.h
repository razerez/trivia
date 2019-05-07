#pragma once

#include "IDatabase.h"
#include "Communicator.h"
#include "RequestHandlerFactory.H"

class Server
{
public:
	Server(IDataBase * db);
	~Server();
	void run();

private:
	IDataBase * _m_database;
	Communicator * _m_communicator;
	RequestHandlerFactory * _m_handlerFactory;

};


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

