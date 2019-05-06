#pragma once

#include <iostream>
#include "IDatabase.h"


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

