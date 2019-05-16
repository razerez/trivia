#include "RequestResult.h"

RequestResult::RequestResult(std::vector<char> response, IRequestHandler * newHandler)
{
	this->_response = response;
	this->_newHandler = newHandler;
}

RequestResult::~RequestResult()
{
	delete(this->_newHandler);
	this->_newHandler = nullptr;
}

std::vector<char> RequestResult::getResponse()
{
	return _response;
}
