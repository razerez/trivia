#include "Game.h"



Game::Game(std::vector<Question> _m_questions, std::map<LoggedUser*, GameData*> _m_players)
{
	this->_m_players = _m_players;
	this->_m_questions = _m_questions;
	this->currect = nullptr;
	shuffleQuestions();
	
}

Game::~Game()
{
}

void Game::shuffleQuestions()
{
	this->currect = new int(this->_m_questions.size());
	int counter = 0;
	for (std::vector<Question>::iterator it = this->_m_questions.begin(); it != this->_m_questions.end(); ++it)
	{
		currect[counter] = (*it).shufleQuestion();
	}
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
	std::string username = user.getUsername();
	int answerId = 0;
	for (std::map<LoggedUser*, GameData*>::iterator it = this->_m_players.begin(); it != this->_m_players.end(); ++it)
	{
		if (answer = this->currect[it->second->_currectAnswerCount + it->second->_wrongAnswerCount])
		{
			answerId = this->currect[it->second->_currectAnswerCount + it->second->_wrongAnswerCount];
			it->second->_currectAnswerCount++;
		}
		else
		{
			it->second->_wrongAnswerCount++;
		}
		it->second->_averangeAnswerTime += clock;
	}
	return answerId;
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

GetGameResultsResponse Game::getPlayerResult()
{
	std::vector<PlayerResults> vec;
	for (std::map<LoggedUser*, GameData*>::iterator it = this->_m_players.begin(); it != this->_m_players.end(); ++it)
	{
		vec.push_back(myPlayer((*it->first), (*it->second)));
	}
	return GetGameResultsResponse(1, vec);
}

PlayerResults Game::myPlayer(LoggedUser user, GameData data)
{
	return PlayerResults(user.getUsername(), data._currectAnswerCount, data._wrongAnswerCount, (data._averangeAnswerTime / (data._currectAnswerCount + data._wrongAnswerCount)));
}




