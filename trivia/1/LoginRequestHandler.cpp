#include "LoginRequestHandler.h"

/*
step 1) deserialize
step 2) the action
step 3) serialize
step 4) nextHandler
*/

LoginRequestHandler::LoginRequestHandler(LoginManager * m_loginManager, RequestHandlerFactory * m_handlerFactory, LoggedUser username) :_m_username(username)
{
	this->_m_loginManager = m_loginManager;
	this->_m_handlerFactory = m_handlerFactory;
}

LoginRequestHandler::~LoginRequestHandler()
{
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



RequestResult LoginRequestHandler::handleRequest(Request req, SOCKET socket)
{
	char reqId = req._buffer[0];
	if (reqId == 'I' )
	{
		return login(req, socket);
	}
	else if (reqId == 'U')
	{
		return signup(req, socket);
	}
	else if (reqId == 'O')
	{
		return logout(req, socket);
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

RequestResult LoginRequestHandler::login(Request req,SOCKET socket)
{
	LoginRequest user = JsonRequestPacketDeserializer().deserializeLoginRequest(req._buffer);
	int stat = this->_m_loginManager->login(user._username, user._password,socket);
	std::string str = "";
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(LoginResponse(stat));
	IRequestHandler* nextHandler=this;
	if (stat)//nitay check this out 
		nextHandler = _m_handlerFactory->createMenuRequestHandler(LoggedUser(user._username, socket));
	return RequestResult(buff, nextHandler);
}

RequestResult LoginRequestHandler::signup(Request req, SOCKET socket)
{
	SignupRequest user = JsonRequestPacketDeserializer().deserializeSignupRequest(req._buffer);
	int stat = this->_m_loginManager->signup(user._username, user._password, user._email, socket);
	std::string str = "";
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(SignupResponse(stat));
	IRequestHandler* nextHandler = this;
	if (stat)
		nextHandler = _m_handlerFactory->createMenuRequestHandler(LoggedUser(user._username, socket));
	return RequestResult(buff, nextHandler);
}


RequestResult LoginRequestHandler::logout(Request req, SOCKET socket)
{
	LogoutRequest user = JsonRequestPacketDeserializer().deserializeLogoutRequest(req._buffer);
	int stat = this->_m_loginManager->logout(user._username);
	string str = "";
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(LogoutResponse(stat));
	IRequestHandler* nextHandler = _m_handlerFactory->createLoginRequestHandler(LoggedUser("", socket));
	return RequestResult(buff, nextHandler);
}



