#include "IRequestHandler.h"

IRequestHandler::IRequestHandler()
{
}

IRequestHandler::~IRequestHandler()
{
}

bool IRequestHandler::isRequestRelevant(Request req)
{
	return false;
}

RequestResult IRequestHandler::handleRequest(Request req)
{
	return RequestResult();
}
