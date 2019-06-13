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
	char reqId = req._buffer[0];
	if (reqId == 'I' || reqId == 'U')
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
	else if (reqId == 'O' || reqId=='X')
	{
		return logout(req);
	}

}


RequestResult LoginRequestHandler::login(Request req)
{
	LoginRequest user = JsonRequestPacketDeserializer().deserializeLoginRequest(req._buffer);
	int stat = this->_m_loginManager->login(user._username, user._password);
	std::string str = "";
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(LoginResponse(stat));
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);
}

RequestResult LoginRequestHandler::signup(Request req)
{
	SignupRequest user = JsonRequestPacketDeserializer().deserializeSignupRequest(req._buffer);
	int stat = this->_m_loginManager->signup(user._username, user._password, user._email);
	std::string str = "";
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(SignupResponse(stat));
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);;
}


RequestResult LoginRequestHandler::logout(Request req)
{
	LogoutRequest user = JsonRequestPacketDeserializer().deserializeLogoutRequest(req._buffer);
	int stat = this->_m_loginManager->logout(user._username);
	std::string str = "";
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(SignupResponse(stat));
	IRequestHandler* nextHandler = nullptr; //currently there is no next handler
	return RequestResult(buff, nextHandler);;
}



