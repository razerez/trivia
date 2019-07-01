#pragma once
#include "IRequestHandler.h"
#include <WinSock2.h>
#include <Windows.h>
struct IRequestHandler;

struct RequestResult
{
public:
	RequestResult(std::vector<char>, IRequestHandler *,std::vector<SOCKET>);
	RequestResult(std::vector<char>, IRequestHandler *);
	~RequestResult();
	std::vector<char> getResponse();
	IRequestHandler* getNewHandler();
	std::vector<char> _response;
	IRequestHandler * _newHandler;
	std::vector<SOCKET> _m_whoToSendTo;
};