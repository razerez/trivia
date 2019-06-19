#pragma once

#include "IDatabase.h"
#include <map>
#include "LoggedUser.h"


class HighscoreTable
{
private:
	IDataBase * _m_database;
public:
	HighscoreTable(IDataBase * database);
	~HighscoreTable();
	 std::map<LoggedUser*, int> getHighscores();


};