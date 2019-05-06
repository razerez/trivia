#pragma once
#include "Request.h"
#include "RequestResult.h"
#include <ctime>
#include <vector>
struct IRequestHandler
{
public:
	IRequestHandler();
	~IRequestHandler();
	bool isRequestRelevant(Request req);
	RequestResult handleRequest(Request req);
private:
};
