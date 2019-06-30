#include "LoggedUser.h"
#include <string>

LoggedUser::LoggedUser(std::string _m_username,SOCKET socket)
{
	this->_m_username = _m_username;
	_m_socket = socket;
}

LoggedUser::~LoggedUser()
{
}

std::string LoggedUser::getUsername()
{
	return this->_m_username;
}

SOCKET LoggedUser::getSocket()
{
	return _m_socket;
}
