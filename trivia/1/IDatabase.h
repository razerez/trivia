#pragma once

#include <iostream>
#include <map>
#include <list>
#include "LoggedUser.h"
#include "Question.h"

using std::list;
using std::map;
using std::string;
using std::vector;
using std::cout;
using std::endl;

class IDataBase
{
public:
	IDataBase();
	~IDataBase();

	virtual map<LoggedUser, int> getHighscores() = 0;
	virtual bool doesUserExiste(string name) = 0;
	virtual void addUserToDB(string name, string password, string email) = 0;
	virtual list<Question> getQuestions(int numberOfQuestions) = 0;

private:
	list<Question> _questions;
};



