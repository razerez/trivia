#include "SqliteDatabase.h"

int ret;


int returnIntegerCallback(void *data, int argc, char **argv, char** azColName)
{
	ret = atoi(argv[0]);
	return 0;
}

void returnQuestionsCallback(void *data, int argc, char **argv, char** azColName)
{
	list<Question>h=*(list<Question>*) data;
	string question = argv[1];
	vector<string> ans;
	ans.push_back(argv[2]);
	ans.push_back(argv[3]);
	ans.push_back(argv[4]);
	ans.push_back(argv[5]);
	h.push_back(Question(question, ans));
}

bool SqliteDatabase::sendMessage(string req)
{
	int res;
	char * errMessage = nullptr;
	res=sqlite3_exec(_db, req.c_str(), returnIntegerCallback, nullptr, &errMessage);
	if (res != SQLITE_OK)
		return false;
	return true;
}
void SqliteDatabase::clean()
{
}

SqliteDatabase::SqliteDatabase() : IDataBase()
{
	string dbFileName = "TriviaDB.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &_db);
	if (res != SQLITE_OK)
	{
		cout << "Failed to open the DB" << endl;
		_db = nullptr;
		return;
	}
	if (doesFileExist == 0)//the file exists already
		return;
	else //create a new one
	{
		vector<string> reqs;
		reqs.push_back("CREATE TABLE User (User TEXT PRIMARY KEY NOT NULL, Password TEXT NOT NULL, Email TEXT NOT NULL); ");

		reqs.push_back("CREATE TABLE Question(question_id INTEGER PRIMARY KEY NOT NULL, question TEXT NOT NULL, correct_ans TEXT NOT NULL, ans2 TEXT NOT NULL, ans3 TEXT NOT NULL, ans4 TEXT NOT NULL);");
		
		reqs.push_back("CREATE TABLE Game(game_id INTEGER PRIMARY KEY NOT NULL, status TEXT NOT NULL, start_time TEXT NOT NULL, end_time TEXT NOT NULL); ");

		for (int i = 0; i < 3;i++)
			sendMessage(reqs[i]);
	}
}


SqliteDatabase::~SqliteDatabase()
{
	// CLEAR AND DELETE DATA TYPES
	sqlite3_close(_db);
	_db = nullptr;
}

map<LoggedUser, int> SqliteDatabase::getHighscores()
{
	map<LoggedUser, int> mp;
	return mp;
}

bool SqliteDatabase::doesUserExiste(string name)
{
	string strSqlStatement = "SELECT COUNT(*) FROM User WHERE user = " + name + ";";
	char * errMessage = nullptr;
	sqlite3_exec(this->_db, strSqlStatement.c_str(), returnIntegerCallback, nullptr, &errMessage);
	return ret;

}

void SqliteDatabase::addUserToDB(string name, string password,string email)
{
	string strSqlStatement = "INSERT INTO User(user, password, email) VALUES('"+ name +"', '" +password + "', '" + email+ "'); ";
	sendMessage(strSqlStatement);
}


list<Question> SqliteDatabase::getQuestions(int numberOfQuestions)
{
	list<Question> s;
	char * errMessage = nullptr;
	string strSqlStatement = "SELECT * FROM Question ORDER BY random() LIMIT " + std::to_string(numberOfQuestions) + ";";
	sqlite3_exec(this->_db, strSqlStatement.c_str(), returnIntegerCallback, &s, &errMessage);
	return s;
}
