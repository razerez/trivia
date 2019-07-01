#include "MyStatusReport.h"

MyStatusReport::MyStatusReport(IDataBase* database)
{
	this->_m_database = database;
}

MyStatusReport::~MyStatusReport()
{
}

MyStatusResponse MyStatusReport::getReport(LoggedUser user)
{
	string username = user.getUsername();
	return 	MyStatusResponse(_m_database->numberOfGamesOfUser(username), _m_database->numberOfRightOrWrongAnswers(username,1), _m_database->numberOfRightOrWrongAnswers(username,0), _m_database->avgTimeForAnsOfUser(username));
}
