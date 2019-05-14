#pragma once

#include <iostream>
#include "IDatabase.h"
#include <map>
#include <list>
#include "LoggedUser.h"
#include "Question.h"

#include "sqlite3.h"
#include <io.h>
#include <queue>
#include <string>



class SqliteDatabase : public IDataBase
{
public:
	SqliteDatabase(list<Question> questions);
	~SqliteDatabase();

	virtual map<LoggedUser, int> getHighscores();
	virtual bool doesUserExist(string name);
	virtual void addUserToDB(string name, string password, string email);
	virtual list<Question> getQuestions(int numberOfQuestions);
private:
	sqlite3 *_db;
	bool sendMessage(string req);
	void clean();
	
};

