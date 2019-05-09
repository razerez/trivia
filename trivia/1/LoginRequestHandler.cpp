#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager* m_loginManager, RequestHandlerFactory* m_handlerFacroty)
{
	this->_m_loginManager = m_loginManager;
	this->_m_handlerFacroty = m_handlerFacroty;
}

LoginRequestHandler::~LoginRequestHandler()
{
	delete(this->_m_handlerFacroty);
	this->_m_handlerFacroty = nullptr;
	delete(this->_m_loginManager);
	this->_m_loginManager = nullptr;
}

bool LoginRequestHandler::isRequestRelevant(Request req)
{
	return false;
}

RequestResult LoginRequestHandler::handleRequest(Request req)
{
	std::vector<char> a('x');
	IRequestHandler* b = new LoginRequestHandler(this->_m_loginManager, this->_m_handlerFacroty);
	return RequestResult(a, b);
}

RequestResult LoginRequestHandler::login(Request req)
{
	std::vector<char> a('x');
	IRequestHandler* b = new LoginRequestHandler(this->_m_loginManager, this->_m_handlerFacroty);
	return RequestResult(a, b);
}

RequestResult LoginRequestHandler::signup(Request req)
{
	std::vector<char> a('x');
	IRequestHandler* b = new LoginRequestHandler(this->_m_loginManager, this->_m_handlerFacroty);
	return RequestResult(a, b);
}
