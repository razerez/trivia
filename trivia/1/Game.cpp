#include "Game.h"


Game::Game(std::vector<Question> _m_questions, std::map<LoggedUser*, GameData*> _m_players)
{
	this->_m_players = _m_players;
	this->_m_questions = _m_questions;
	this->currect = 0;
	this->pos = 0;
}

Game::~Game()
{
}

void Game::removePlayer(LoggedUser user)
{

	std::string username = user.getUsername();
	bool flag = true;
	int counter = 0;

	for (std::map<LoggedUser*, GameData*>::iterator it = this->_m_players.begin(); it != this->_m_players.end(); ++it)
	{
		if ((it->first)->getUsername() == username)
		{
			this->_m_players.erase(it);
		}
	}
}

int Game::submiteAnswer(int answer, LoggedUser user, float clock)
{
	/*
	std::string username = user.getUsername();
	int isAnswer = 0;
	for (std::map<LoggedUser*, GameData*>::iterator it = this->_m_players.begin(); it != this->_m_players.end(); ++it)
	{
		if ((it->first)->getUsername() == username)
		{
			if (answer == 0)
			{
				isAnswer = 1;
				it->second->_currectAnswerCount++;
			}
			else
			{
				it->second->_wrongAnswerCount++;
			}
			it->second->_averangeAnswerTime += clock;
		}
	}
	return isAnswer;
	*/


	return 1;
}

void Game::getQuestionForUser(LoggedUser user)
{
	for (std::map<LoggedUser*, GameData*>::iterator it = this->_m_players.begin(); it != this->_m_players.end(); ++it)
	{
		if (user.getUsername() == it->first->getUsername())
		{
			it->second->_currectQuestion = this->_m_questions[it->second->_wrongAnswerCount + it->second->_currectAnswerCount];
		}
	}
}

PlayerResults Game::getPlayerResult(LoggedUser user)
{

	PlayerResults myResult("", 1, 1, 1);


	std::string username = user.getUsername();
	for (std::map<LoggedUser*, GameData*>::iterator it = this->_m_players.begin(); it != this->_m_players.end(); ++it)
	{
		if ((it->first)->getUsername() == username)
		{

			myResult._username = it->first->getUsername();
			myResult._correctAnswerCount = it->second->_currectAnswerCount;
			myResult._wrongAnswerCount = it->second->_wrongAnswerCount;
			myResult._averageAnswerTime = it->second->_averangeAnswerTime;
			break;
		}
	}
	return myResult;
}


