#include "SqliteDatabase.h"

int ret;
float floatRet;

int returnIntegerCallback(void *data, int argc, char **argv, char** azColName)
{
	ret = atoi(argv[0]);
	return 0;
}
int returnFloatCallback(void* data, int argc, char** argv, char** azColName)
{
	floatRet = atof(argv[0]);
	return 0;
}

int returnQuestionsCallback(void *data, int argc, char **argv, char** azColName)
{
	list<Question>h = *(list<Question>*) data;
	string question = argv[1];
	vector<string> ans;
	ans.push_back(argv[2]);
	ans.push_back(argv[3]);
	ans.push_back(argv[4]);
	ans.push_back(argv[5]);
	h.push_back(Question(question, ans));
	return 0;
}

int returnHighScoreCallback(void *data, int argc, char **argv, char** azColName)
{
	LoggedUser * user=new LoggedUser(argv[0]);
	int score = std::stoi(argv[1]);
	std::pair<LoggedUser*, int> p(user, score);
	(*(std::map<LoggedUser*, int>*) data).insert(p);
	return 0;
}

bool SqliteDatabase::sendMessage(string req)
{
	int res;
	char * errMessage = nullptr;
	res = sqlite3_exec(_db, req.c_str(), returnIntegerCallback, nullptr, &errMessage);
	if (res != SQLITE_OK)
		return false;
	return true;
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
		reqs.push_back("CREATE TABLE User (username TEXT PRIMARY KEY NOT NULL, password TEXT NOT NULL, email TEXT NOT NULL); ");
		reqs.push_back("CREATE TABLE Question(question_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, question TEXT NOT NULL, correct_ans TEXT NOT NULL, ans2 TEXT NOT NULL, ans3 TEXT NOT NULL, ans4 TEXT NOT NULL);");
		reqs.push_back("CREATE TABLE Game(game_id INTEGER PRIMARY KEY NOT NULL, status TEXT NOT NULL, start_time DATETIME NOT NULL, end_time DATETIME NOT NULL); ");
		reqs.push_back("CREATE TABLE PlayersAnswers(game_id INTEGER NOT NULL, username TEXT NOT NULL, question_id integer not null, player_answer text not null, is_correct integer not null, answer_time integer not null, primary key(game_id, username, question_id), foreign key(game_id) REFERENCES Game(game_id), foreign key(username) REFERENCES User(username), foreign key(question_id) REFERENCES Question(question_id));");
		for (int i = 0; i < reqs.size(); i++)
			sendMessage(reqs[i]);
	}
}


SqliteDatabase::~SqliteDatabase()
{
	// CLEAR AND DELETE DATA TYPES
	sqlite3_close(_db);
	_db = nullptr;
}

map<LoggedUser*, int> SqliteDatabase::getHighscores()
{
	//s.clear();
	map<LoggedUser*, int>*s=new map<LoggedUser*,int>();
	string strSqlStatement = "SELECT username, count(*) FROM PlayersAnswers where is_correct = 1 group by username order by count(*) desc limit 3;";
	char * errMessage = nullptr;
	sqlite3_exec(this->_db, strSqlStatement.c_str(), returnHighScoreCallback,s, &errMessage);
	return *s;
}

bool SqliteDatabase::doesUserExiste(string name)
{
	string strSqlStatement = "SELECT COUNT(*) FROM User WHERE username = '" + name + "';";
	char * errMessage = nullptr;
	sqlite3_exec(this->_db, strSqlStatement.c_str(), returnIntegerCallback, nullptr, &errMessage);
	return ret;

}

bool SqliteDatabase::doesPasswordExist(string name, string password)
{
	string strSqlStatement = "SELECT COUNT(*) FROM User WHERE username = '" + name + "' and password = '" + password + "';";
	char * errMessage = nullptr;
	sqlite3_exec(this->_db, strSqlStatement.c_str(), returnIntegerCallback, nullptr, &errMessage);
	return ret;
}

void SqliteDatabase::addUserToDB(string name, string password, string email)
{
	string strSqlStatement = "INSERT INTO User(username, password, email) VALUES('" + name + "', '" + password + "', '" + email + "'); ";
	sendMessage(strSqlStatement);
}


list<Question> SqliteDatabase::getQuestions(int numberOfQuestions)
{
	list<Question> s;
	char * errMessage = nullptr;
	string strSqlStatement = "SELECT * FROM Question ORDER BY random() LIMIT " + std::to_string(numberOfQuestions) + ";";
	sqlite3_exec(this->_db, strSqlStatement.c_str(), returnQuestionsCallback, &s, &errMessage);
	return s;
}
int SqliteDatabase::numberOfRightOrWrongAnswers(string user, bool right)
{
	string strSqlStatement = "SELECT count(*) FROM PlayersAnswers where is_correct = " + std::to_string(right) + " and username='" + user + "' group by username;";
	char* errMessage = nullptr;
	sqlite3_exec(this->_db, strSqlStatement.c_str(), returnIntegerCallback, nullptr, &errMessage);
	return ret;
}
int SqliteDatabase::numberOfGamesOfUser(string user)
{
	string strSqlStatement = "SELECT count(DISTINCT game_id) FROM PlayersAnswers where username = '" + user + "' group by username";
	char* errMessage = nullptr;
	sqlite3_exec(this->_db, strSqlStatement.c_str(), returnIntegerCallback, nullptr, &errMessage);
	return ret;
}
float SqliteDatabase::avgTimeForAnsOfUser(string user)
{
	string strSqlStatement = "SELECT avg(answer_time) FROM PlayersAnswers where username='" + user + "';";
	char* errMessage = nullptr;
	sqlite3_exec(this->_db, strSqlStatement.c_str(), returnFloatCallback, nullptr, &errMessage);
	return floatRet;
}