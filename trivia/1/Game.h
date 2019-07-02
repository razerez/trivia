#pragma once


#include "LoggedUser.h"
#include "GameData.h"
#include "Question.h"
#include "GetGameResultsResponse.h"
#include "GetQuestionResponse.h"
#include "PlayerResults.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <map>


class Game
{
	std::vector<Question> _m_questions;
	std::map<LoggedUser*, GameData*> _m_players;
	int * currect;
	PlayerResults myPlayer(LoggedUser user, GameData data);

public:
	
	Game(std::vector<Question> _m_questions, std::map<LoggedUser*, GameData*> _m_players);
	~Game();

	void shuffleQuestions();
	void removePlayer(LoggedUser user);
	int submiteAnswer(int answer, LoggedUser user,float clock);
	void getQuestionForUser(LoggedUser user);
	GetGameResultsResponse getPlayerResult();

};
