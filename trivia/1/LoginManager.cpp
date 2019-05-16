#include "LoginManager.h"


LoginManager::LoginManager(IDataBase * dataBase, vector<LoggedUser> loggedUsers)
{
	this->_m_dataBase = dataBase;
	this->_m_loggedUsers = loggedUsers;
}

LoginManager::~LoginManager()
{
}

void LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (!this->_m_dataBase->doesUserExiste(username))
	{
		this->_m_dataBase->addUserToDB(username, password, email);
		LoggedUser newUser(username);
		this->_m_loggedUsers.push_back(newUser);
	}
}


void LoginManager::login(std::string username, std::string password)
{
	if (!this->_m_dataBase->doesUserExiste(username))
	{
		LoggedUser newUser(username);
		this->_m_loggedUsers.push_back(newUser);
	}
}

void LoginManager::logout()
{
	this->_m_loggedUsers.clear();
}
