#pragma once

#include <iostream>
#include <map>
#include <list>
#include "LoggedUser.h"
#include "Question.h"

using namespace std;

class IDataBase
{
public:
	IDataBase(list<Question> questions);
	~IDataBase();

	virtual map<LoggedUser, int> getHighscores() = 0;
	virtual bool doesUserExiste(string name) = 0;
	virtual list<Question> getQuestions(int numberOfQuestions) = 0;

private:
	list<Question> _questions;
};



