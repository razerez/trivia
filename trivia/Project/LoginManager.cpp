#include "LoginManager.h"


LoginManager::LoginManager(IDataBase * dataBase)
{
	this->_m_dataBase = dataBase;
}

LoginManager::~LoginManager()
{

}

void LoginManager::signup(std::string username, std::string password, std::string email)
{

}


void LoginManager::login(std::string username, std::string password)
{

}

void LoginManager::logout()
{

}
