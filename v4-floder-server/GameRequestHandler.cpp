#include "GameRequestHandler.h"



RequestResult GameRequestHandler::getQuestion(Request req)
{
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(this->_m_game->getQuestionForUser(this->_m_username));
	IRequestHandler * nextHandler = this;
	return RequestResult(buff, nextHandler);
}

RequestResult GameRequestHandler::submitAnswer(Request req)
{
	SubmitAnswerRequest userAnswer = JsonRequestPacketDeserializer().deserializeSubmitAnswerRequest(req._buffer);
	int isOk = this->_m_game->submiteAnswer(userAnswer._m_answerID, this->_m_username, 0);
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse(1, isOk));
	IRequestHandler * nextHandler = this;
	return RequestResult(buff, nextHandler);
}

RequestResult GameRequestHandler::getGameResult(Request req)
{
	std::vector<char> buff = JsonResponsePacketSerializer::serializeResponse(this->_m_game->getPlayerResult());
	IRequestHandler * nextHandler = this;
	return RequestResult(buff, nextHandler);
}

RequestResult GameRequestHandler::leaveGame(Request req)
{
	vector<char> buff = JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse(this->_m_game->removePlayer(this->_m_username)));
	IRequestHandler * nextHandler = this->_m_HandlerFactory->createMenuRequestHandler(this->_m_username);
	return RequestResult(buff, nullptr);
}

GameRequestHandler::GameRequestHandler(LoggedUser * username, RequestHandlerFactory * m_handlerFactory, Game * m_game, GameManager * m_gameManager): _m_username(*username)
{
	this->_m_HandlerFactory = m_handlerFactory;
	this->_m_game = m_game;
	this->_m_gameManager = m_gameManager;

}

GameRequestHandler::~GameRequestHandler()
{
}

LoggedUser GameRequestHandler::getUsername()
{
	return _m_username;
}

void GameRequestHandler::setUsername(LoggedUser username)
{
	_m_username = username;
}

bool GameRequestHandler::isRequestRelevant(Request req)
{
	char reqId = req._buffer[0];
	if (reqId == 'Q' || reqId == 'A' || reqId == 'Z' || reqId == 'W')
	{
		return true;
	}
	return false;
}

RequestResult GameRequestHandler::handleRequest(Request request, SOCKET socket)
{
	char reqId = request._buffer[0];
	if (reqId == 'Q')
	{
		return getQuestion(request);
	}
	else if (reqId == 'A')
	{
		return submitAnswer(request);
	}
	else if (reqId == 'Z')
	{
		return getGameResult(request);
	}
	else if (reqId == 'W')
	{
		return leaveGame(request);
	}

}

