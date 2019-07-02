#include "GameRequestHandler.h"

RequestResult GameRequestHandler::getQuestion(Request req)
{
	return RequestResult(vector<char>(), nullptr);
}

RequestResult GameRequestHandler::submitAnswer(Request req)
{
	return RequestResult(vector<char>(), nullptr);
}

RequestResult GameRequestHandler::getGameResult(Request req)
{
	return RequestResult(vector<char>(), nullptr);
}

RequestResult GameRequestHandler::leaveGame(Request req)
{
	return RequestResult(vector<char>(), nullptr);
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
	return false;
}

RequestResult GameRequestHandler::handleRequest(Request request, SOCKET socket)
{
	return RequestResult(vector<char>(), nullptr);
}
