#pragma once
#include "IRequestHandler.h"
struct RequestResult
{
public:
	RequestResult(std::vector<char> response, IRequestHandler * newHandler);
	~RequestResult();

private:
	std::vector<char> _response;
	IRequestHandler * _newHandler;
};