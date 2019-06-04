#include "LoginManager.h"


LoginManager::LoginManager(IDataBase * dataBase, vector<LoggedUser> loggedUsers)
{
	this->_m_dataBase = dataBase;
	this->_m_loggedUsers = loggedUsers;
}

LoginManager::~LoginManager()
{
}

int LoginManager::signup(std::string username, std::string password, std::string email)
{
	int isOk = int(this->_m_dataBase->doesUserExiste(username));

	if (isOk == 0)
	{
		this->_m_dataBase->addUserToDB(username, password, email);
		LoggedUser newUser(username);
		this->_m_loggedUsers.push_back(newUser);
		return 1;
	}
	return 0;
}


int LoginManager::login(std::string username, std::string password)
{

	int isOk = int(this->_m_dataBase->doesUserExiste(username));
	int isPasswordOk = int(this->_m_dataBase->doesPasswordExist(username, password));
	if (isOk && isPasswordOk)
	{
		LoggedUser newUser(username);
		this->_m_loggedUsers.push_back(newUser);
		return 1;
	}
	return 0;
}

int LoginManager::logout(std::string username)
{
	try
	{
		bool flag = true;
		int counter = 0;

		for (std::vector<LoggedUser>::iterator i = this->_m_loggedUsers.begin(); i != this->_m_loggedUsers.end() && flag; ++i)
		{
			if ((*i).getUsername() == username)
			{
				flag = !false;
			}
			counter++;
		}
		_m_loggedUsers.erase(_m_loggedUsers.begin() + counter);
		return 1;
	}
	catch (...)
	{
		return 0;
	}
}

