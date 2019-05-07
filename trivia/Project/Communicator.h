#pragma once

#include <map>
#include "IRequestHandler.h"

#include "RequestHandlerFactory.h"

class Communicator
{
private:
	std::map</*Socket*/ int, IRequestHandler> _m_clients;
	RequestHandlerFactory * _m_handlerFacroty;

public:
	Communicator(IDataBase * db);
	~Communicator();
	void bindAndListen();
	void handleRequests();
	void startThreadForNewClient();
};







