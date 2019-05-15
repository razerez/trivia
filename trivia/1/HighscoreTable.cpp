#include "HighscoreTable.h"

HighscoreTable::HighscoreTable(IDataBase * database)
{
	this->_m_database = database;
}

HighscoreTable::~HighscoreTable()
{
}

std::map<LoggedUser, int> HighscoreTable::getHighscores()
{
	return this->_m_database->getHighscores();
}

