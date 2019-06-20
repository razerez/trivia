#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager* m_loginManager, RequestHandlerFactory* m_handlerFactory) :_m_username("")
{
	this->_m_loginManager = m_loginManager;
	this->_m_handlerFactory = m_handlerFactory;
}

LoginRequestHandler::LoginRequestHandler(LoginManager * m_loginManager, RequestHandlerFactory * m_handlerFactory, LoggedUser username) :_m_username(username)
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
	char reqId = req._buffer[0];
	if (reqId == 'I' || reqId == 'U'|| reqId == 'O')
	{
		return true;
	}
	return false;
}



RequestResult LoginRequestHandler::handleRequest(Request req)
{
	char reqId = req._buffer[0];
	if (reqId == 'I' )
	{
		return login(req);
	}
	else if (reqId == 'U')
	{
		return signup(req);
	}
	else if (reqId == 'O')
	{
		return logout(req);
	}
	else if (reqId == 'X')
	{
		return exit(req);
	}
}

LoggedUser LoginRequestHandler::getUsername()
{
	return _m_username;
}

void LoginRequestHandler::setUsername(LoggedUser username)
{
	_m_username = username;
}


RequestResult LoginRequestHandler::exit(Request req)
{
	LogoutRequest user = JsonRequestPacketDeserializer().deserializeLogoutRequest(req._buffer);
	int stat = this->_m_loginManager->logout(user._username);
	std::vector<char> buff;
	IRequestHandler* nextHandler = nullptr;
	return RequestResult(buff, nextHandler);

}

RequestResult LoginRequestHandler::login(Request req)
{
	LoginRequest user = JsonRequestPacketDeserializer().deserializeLoginRequest(req._buffer);
	int stat = this->_m_loginManager->login(user._username, user._password);
	std::string str = "";
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(LoginResponse(stat));
	IRequestHandler* nextHandler=this;
	if (stat)//nitay check this out 
		nextHandler = _m_handlerFactory->createMenuRequestHandler(LoggedUser(user._username));
	return RequestResult(buff, nextHandler);
}

RequestResult LoginRequestHandler::signup(Request req)
{
	SignupRequest user = JsonRequestPacketDeserializer().deserializeSignupRequest(req._buffer);
	int stat = this->_m_loginManager->signup(user._username, user._password, user._email);
	std::string str = "";
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(SignupResponse(stat));
	IRequestHandler* nextHandler = this;
	if (stat)
		nextHandler = _m_handlerFactory->createMenuRequestHandler(LoggedUser(user._username));
	return RequestResult(buff, nextHandler);
}


RequestResult LoginRequestHandler::logout(Request req)
{
	LogoutRequest user = JsonRequestPacketDeserializer().deserializeLogoutRequest(req._buffer);
	int stat = this->_m_loginManager->logout(user._username);
	std::string str = "";
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(LogoutResponse(stat));
	IRequestHandler* nextHandler = _m_handlerFactory->createLoginRequestHandler(LoggedUser(""));
	return RequestResult(buff, nextHandler);
}



