#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase(list<Question> questions) : IDataBase(questions)
{
}
	
	
SqliteDatabase::~SqliteDatabase()
{

}

map<LoggedUser, int> SqliteDatabase::getHighscores()
{
	map<LoggedUser, int> mp;
	return mp;
}

bool SqliteDatabase::doesUserExiste(string name)
{
	return false;
}
list<Question> SqliteDatabase::getQuestions(int numberOfQuestions)
{
	list<Question> s;
	return s;
}