#include "LoggedUser.h"
#include <string>

LoggedUser::LoggedUser(std::string _m_username)
{
	this->_m_username = _m_username;
}

LoggedUser::~LoggedUser()
{
}

std::string LoggedUser::getUsername()
{
	return this->_m_username;
}
