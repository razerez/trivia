#pragma once
#include "Request.h"
#include "RequestResult.h"
#include <ctime>
#include <vector>
struct RequestResult;
struct IRequestHandler
{
public:
	IRequestHandler();
	~IRequestHandler();
	virtual bool isRequestRelevant(Request req) = 0;
	virtual RequestResult handleRequest(Request req) = 0;
};
