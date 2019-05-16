#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

#include <thread>
#include <mutex>
#include <exception>

#include <string>
#include <queue>
#include <map>

#include "Helper.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#define PORT 8821

class Communicator
{
private:
	Request getMessageFromClient();
	std::map<SOCKET, IRequestHandler*> _m_clients;
	RequestHandlerFactory * _m_handlerFacroty;
	SOCKET serverSocket;
	void clientHandler(SOCKET socket);
	string vectorCharToString(vector<char> v);
	vector<char> stringToVectorChar(string str);
	void sendMsg(string message, SOCKET sc);
public:
	Communicator(IDataBase * db);
	~Communicator();
	void bindAndListen();
	void handleRequests();
	void startThreadForNewClient();
};
