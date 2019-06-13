#pragma once
#pragma comment (lib, "ws2_32.lib")
//#pragma comment (lib, "ws2_32.lib")
#include "IDatabase.h"
#include "Communicator.h"
#include "RequestHandlerFactory.H"
#include "WSAInitializer.h"
#include <exception>
class Server
{
public:
	Server(IDataBase * db);
	~Server();
	void run();

private:
	IDataBase * _m_database;
	Communicator * _m_communicator;
	WSAInitializer wsaInit;
};
