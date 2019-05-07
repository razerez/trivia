#pragma once
#include "IRequestHandler.h"

struct IRequestHandler;

struct RequestResult
{
public:
	RequestResult(std::vector<char>, IRequestHandler *);
	~RequestResult();

private:
	std::vector<char> _response;
	IRequestHandler * _newHandler;
};