#include "LoginManager.h"

std::mutex mutexLock;

LoginManager::LoginManager(IDataBase * dataBase, vector<LoggedUser> loggedUsers)
{
	this->_m_dataBase = dataBase;
	this->_m_loggedUsers = loggedUsers;
}

LoginManager::~LoginManager()
{
}

int LoginManager::signup(std::string username, std::string password, std::string email,SOCKET socket)
{
	std::unique_lock<std::mutex> myLock(mutexLock);
	int isOk = int(this->_m_dataBase->doesUserExiste(username));
	myLock.unlock();

	if (isOk == 0)
	{
		std::unique_lock<std::mutex> myLock(mutexLock);
		this->_m_dataBase->addUserToDB(username, password, email);
		LoggedUser newUser(username,socket);
		std::cout << username << " Signed Up" << std::endl;
		this->_m_loggedUsers.push_back(newUser);
		myLock.unlock();
		return 1;
	}
	return 0;
}


int LoginManager::login(std::string username, std::string password,SOCKET socket)
{
	std::unique_lock<std::mutex> myLock(mutexLock);
	int isOk = int(this->_m_dataBase->doesUserExiste(username));
	int isPasswordOk = int(this->_m_dataBase->doesPasswordExist(username, password));
	myLock.unlock();

	bool flag = true;
	int counter = 0;

	for (std::vector<LoggedUser>::iterator i = this->_m_loggedUsers.begin(); i != this->_m_loggedUsers.end() && flag; ++i)
	{
		if ((*i).getUsername() == username)
		{
			flag = !flag;
		}
		counter++;
	}


	if (isOk && isPasswordOk && flag)
	{
		LoggedUser newUser(username,socket);
		std::cout << username <<" Logged In"<< std::endl;
		std::unique_lock<std::mutex> myLock(mutexLock);
		this->_m_loggedUsers.push_back(newUser);
		myLock.unlock();
		return 1;
	}
	return 0;
}

int LoginManager::logout(std::string username)
{
	try
	{
		std::unique_lock<std::mutex> myLock(mutexLock);
		bool flag = true;
		int counter = 0;

		for (std::vector<LoggedUser>::iterator i = this->_m_loggedUsers.begin(); i != this->_m_loggedUsers.end() && flag; ++i)
		{
			if ((*i).getUsername() == username)
			{
				flag = !flag;
				counter--;
			}
			counter++;
		}
		if(!flag)_m_loggedUsers.erase(_m_loggedUsers.begin() + counter);
		myLock.unlock();
		std::cout << username << " Logged Out" << std::endl;
		return 1;
	}
	catch (...)
	{
		return 0;
	}
}


