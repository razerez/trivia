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
	SqliteDatabase();
	~SqliteDatabase();
	virtual int numberOfRightOrWrongAnswers(string user, bool right);
	virtual int numberOfGamesOfUser(string user);
	virtual float avgTimeForAnsOfUser(string user);
	virtual map<LoggedUser*, int> getHighscores();
	virtual bool doesUserExiste(string name);
	virtual bool doesPasswordExist(string name, string password);
	virtual void addUserToDB(string name, string password, string email);
	virtual vector<Question> getQuestions(int numberOfQuestions);
	virtual int addNewGame();
	virtual void updateGame(int gameID);
	virtual void updateAnswer(string username, int gameID, string question, string ans, bool is_correct, int answerTime);
private:
	sqlite3 *_db;
	bool sendMessage(string req);
};
