#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler()
{
}

LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(Request req)
{
	return false;
}

RequestResult LoginRequestHandler::handleRequest(Request req)
{
	std::vector<char> a('x');
	IRequestHandler* b = new LoginRequestHandler();
	return RequestResult(a, b);
}

RequestResult LoginRequestHandler::login(Request req)
{
	std::vector<char> a('x');
	IRequestHandler* b = new LoginRequestHandler();
	return RequestResult(a, b);
}

RequestResult LoginRequestHandler::signup(Request req)
{
	std::vector<char> a('x');
	IRequestHandler* b = new LoginRequestHandler();
	return RequestResult(a, b);
}
