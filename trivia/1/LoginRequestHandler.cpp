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
	char reqId = req.getBuffer()[0];
	if (reqId == 0b00000001 )
	{
		return true;
	}
	return false;
}



RequestResult LoginRequestHandler::handleRequest(Request req)
{
	if (!isRequestRelevant(req))
	{
		throw std::exception("request is not relevant");
	}
	LoginRequest request = deserializeLoginRequest(req.getBuffer());
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



string getBytes(int startPoint, int amount, std::vector<char> buffer)
{
	std::string ret;
	for (size_t i = startPoint; i < amount; i++)
	{
		ret.push_back(buffer[i]);
	}
	return ret;
}