#pragma once

#include "IDatabase.h"
#include "LoggedUser.h"
#include "GameData.h"
#include "Question.h"
#include "GetGameResultsResponse.h"
#include "GetQuestionResponse.h"
#include "PlayerResults.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <map>


class Game
{
	IDataBase * _m_database;
	std::vector<Question> _m_questions;
	std::map<LoggedUser*, GameData*> _m_players;
	vector<int> currect;
	int ID;
	int _pos;
	PlayerResults myPlayer(LoggedUser user, GameData data);

public:
	
	Game(std::vector<Question> _m_questions, std::map<LoggedUser*, GameData*> _m_players, IDataBase * _m_database, int ID);
	~Game();

	void shuffleQuestions();
	void removePlayer(LoggedUser user);
	int submiteAnswer(int answer, LoggedUser user,float clock);
	GetQuestionResponse getQuestionForUser(LoggedUser user);
	GetGameResultsResponse getPlayerResult();

};
