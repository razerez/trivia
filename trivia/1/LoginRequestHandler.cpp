#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager* m_loginManager, RequestHandlerFactory* m_handlerFactory)
{
	this->_m_loginManager = m_loginManager;
	this->_m_handlerFactory = m_handlerFactory;
}

LoginRequestHandler::~LoginRequestHandler()
{
	delete(this->_m_handlerFactory);
	this->_m_handlerFactory = nullptr;
	delete(this->_m_loginManager);
	this->_m_loginManager = nullptr;
}

bool LoginRequestHandler::isRequestRelevant(Request req)
{
	char reqId = req.getBuffer()[0];
	if (reqId == 'I' || reqId == 'U')
	{
		return true;
	}
	return false;
}



RequestResult LoginRequestHandler::handleRequest(Request req)
{
	LoginRequest request = deserializeLoginRequest(req.getBuffer());
	char reqId = req.getBuffer()[0];
	if (reqId == 'I' )
	{
		return login(req);
	}
	else if (reqId == 'U')
	{
		return signup(req);
	}

}


RequestResult LoginRequestHandler::login(Request req)
{
	LoginRequest user = deserializeLoginRequest(req.getBuffer());
	this->_m_loginManager->login(user.getUsername(), user.getPassword());
	std::string str = "";
	std::vector<char> buff = serializeResponse(LoginResponse(1));
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);
}

RequestResult LoginRequestHandler::signup(Request req)
{
	std::vector<char> a('x');
	IRequestHandler* b = new LoginRequestHandler(this->_m_loginManager, this->_m_handlerFactory);
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