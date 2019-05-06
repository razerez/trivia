#pragma once
#include "IRequestHandler.h"
class RequestResult
{
public:
	RequestResult(std::vector<char> response, IRequestHandler * newHandler);
	~RequestResult();

private:
	std::vector<char> _response;
	IRequestHandler * _newHandler;
};