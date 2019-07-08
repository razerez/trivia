#include "Game.h"

std::mutex mutexLockGame;

Game::Game(vector<Question> _m_questions, std::map<LoggedUser*, GameData*> _m_players, IDataBase * _m_database, int ID)
{
	this->_m_players = _m_players;
	this->_m_questions = _m_questions;
	this->_m_database = _m_database;
	this->ID = ID;
	this->_pos = 0;
	shuffleQuestions();
	
}

Game::~Game()
{
}

void Game::shuffleQuestions()
{
	int counter = 0;
	for (vector<Question>::iterator it = this->_m_questions.begin(); it != this->_m_questions.end(); ++it, counter++)
	{
		std::unique_lock<std::mutex> myLock(mutexLockGame);
		currect[counter] = (*it).shufleQuestion();
		myLock.unlock();
	}
}

int Game::removePlayer(LoggedUser user)
{

	try
	{
		bool isRemove = false;
		string username = user.getUsername();
		for (map<LoggedUser*, GameData*>::iterator it = this->_m_players.begin(); it != this->_m_players.end(); ++it)
		{
			if ((it->first)->getUsername() == username)
			{
				isRemove = !isRemove;
				std::unique_lock<std::mutex> myLock(mutexLockGame);
				this->_m_players.erase(it);
				myLock.unlock();
			}
		}
		if (isRemove)
		{
			return 1;
		}
		return 0;
	}
	catch (...)
	{
		return 0;
	}
}

int Game::submiteAnswer(int answer, LoggedUser user, float clock)
{
	std::unique_lock<std::mutex> myLock(mutexLockGame);
	//this->_m_database->updateGame(this->ID);
	myLock.unlock();
	std::string username = user.getUsername();
	int answerId = 0;
	bool isOk = false;
	for (std::map<LoggedUser*, GameData*>::iterator it = this->_m_players.begin(); it != this->_m_players.end(); ++it)
	{
		if (user.getUsername() == it->first->getUsername())
		{
			
			if (answer == this->currect[it->second->_currectAnswerCount + it->second->_wrongAnswerCount])
			{
				std::unique_lock<std::mutex> myLock(mutexLockGame);
				isOk = true;
				answerId = this->currect[it->second->_currectAnswerCount + it->second->_wrongAnswerCount];
				it->second->_currectAnswerCount++;
				myLock.unlock();
			}
			else
			{
				std::unique_lock<std::mutex> myLock(mutexLockGame);
				it->second->_wrongAnswerCount++;
				myLock.unlock();
			}
			std::unique_lock<std::mutex> myLock(mutexLockGame);
			it->second->_averangeAnswerTime += clock;
			//this->_m_database->updateAnswer(it->first->getUsername(), this->ID, it->second->_currectQuestion.getQuestion(), it->second->_currectQuestion.getCurrectAnswer(), isOk, clock);
			myLock.unlock();
		}

	}
	return answerId;
}

GetQuestionResponse Game::getQuestionForUser(LoggedUser user)
{
	string question="";
	map<int, string> answerAndID;
	for (std::map<LoggedUser*, GameData*>::iterator it = this->_m_players.begin(); it != this->_m_players.end(); ++it)
	{
		if (user.getUsername() == it->first->getUsername())
		{
			int counter = 0;
			std::unique_lock<std::mutex> myLock(mutexLockGame);
			it->second->_currectQuestion = this->_m_questions[it->second->_wrongAnswerCount + it->second->_currectAnswerCount];
			question = it->second->_currectQuestion.getQuestion();
			vector<string> answers = it->second->_currectQuestion.getPossibleAnswers();
			for (vector<string>::iterator i=answers.begin();i!=answers.end();i++, counter++)
			{
				answerAndID.insert(std::pair<int, string>(counter,*i));
			}
			myLock.unlock();
		}
	}
	GetQuestionResponse res(1, question,answerAndID);
	return res;
}

GetGameResultsResponse Game::getPlayerResult()
{
	std::unique_lock<std::mutex> myLock(mutexLockGame);
	this->_pos++;
	myLock.unlock();

	int numberOfPlayers = 0;

	while (numberOfPlayers != this->_pos);
	{
		numberOfPlayers = 0;
		for (map<LoggedUser*, GameData*>::iterator it = this->_m_players.begin(); it != this->_m_players.end(); ++it)
		{
			numberOfPlayers++;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}



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




