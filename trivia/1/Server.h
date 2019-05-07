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


