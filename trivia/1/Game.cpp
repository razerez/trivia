#include "Game.h"


Game::Game(std::vector<Question> _m_questions, std::map<LoggedUser, GameData> _m_players)
{
	this->_m_players = _m_players;
	this->_m_questions = _m_questions;
}

Game::~Game()
{
}

void Game::removePlayer(LoggedUser user)
{
}

int Game::submiteAnswer()
{
	return 0;
}

Question Game::getQuestionForUser(LoggedUser user)
{
	std::vector <std::string> vec;
	std::string question;
	return Question(question, vec);
}


