#pragma once


#include "LoggedUser.h"
#include "GameData.h"
#include "Question.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>


class Game
{
	std::vector<Question> _m_questions;
	std::map<LoggedUser, GameData> _m_players;
public:
	
	Game(std::vector<Question> _m_questions, std::map<LoggedUser, GameData> _m_players);
	~Game();

	void removePlayer(LoggedUser user);
	int submiteAnswer();
	Question getQuestionForUser(LoggedUser user);

};
