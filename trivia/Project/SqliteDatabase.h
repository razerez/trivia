#pragma once

#include <iostream>
#include "IDatabase.h"
#include <map>
#include <list>
#include "LoggedUser.h"
#include "Question.h"


class SqliteDatabase : public IDataBase
{
public:
	SqliteDatabase(list<Question> questions);
	~SqliteDatabase();

	virtual map<LoggedUser, int> getHighscores();
	virtual bool doesUserExiste(string name);
	virtual list<Question> getQuestions(int numberOfQuestions);
private:

};

