#pragma once

#include "IDatabase.h"
#include <map>
#include "LoggedUser.h"
#include "MyStatusResponse.h"
class MyStatusReport
{
private:
	IDataBase* _m_database;
public:
	MyStatusReport(IDataBase* database);
	~MyStatusReport();
	MyStatusResponse getReport(LoggedUser user);

};