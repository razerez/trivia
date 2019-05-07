#include "Communicator.h"

Communicator::Communicator(IDataBase * db)
{
	_m_handlerFacroty = new RequestHandlerFactory( db );
}

Communicator::~Communicator()
{
}

void Communicator::bindAndListen()
{
}

void Communicator::handleRequests()
{
}

void Communicator::startThreadForNewClient()
{
}
